import socket
import math
import re
import os
import threading
import uuid
from Core.Request import Request
from Core.Response import Response
from Controllers.LoginController import LoginController

class MyServer:
    FORMAT: str = 'UTF-8'
    BUFFER_SIZE: int = 4096
    PUBLIC_PATH: str = 'public'
    SERVER_IP: str|None = None
    SERVER_PORT: int|None = None
    SERVER_PATH: str = ''

    def __init__(self) -> None:
        self.SERVER_PATH = os.path.join(os.path.dirname(__file__), '..')
        pass

    def Listen(self, server_port: int, server_ip: str|None = None) -> None:
        self.Bootstrap(server_port, server_ip)

        print("[STARTING] Server is starting...")
        self.SERVER.listen(1)

        while True:
            print(f"[LISTENING] Server is listening on {self.SERVER_IP}:{self.SERVER_PORT}")

            connectionSocket, addr = self.SERVER.accept()
            thread = threading.Thread(target=self.ManageConnection, args=(connectionSocket, addr))
            thread.start()
            print(f"[ACTIVE CONNECTIONS] {threading.activeCount()-1}")

    def Bootstrap(self, server_port:int, server_ip: str|None = None) -> None:
        self.SERVER_PORT = server_port

        if server_ip is None:
            self.SERVER_IP = socket.gethostbyname(socket.gethostname())
        else:
            self.SERVER_IP = server_ip

        ADRR = (self.SERVER_IP, self.SERVER_PORT)

        self.SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.SERVER.bind(ADRR)

    def ManageConnection(self, connSocket: socket.socket, addrSocket):
        print(f"[NEW CONNECTION] {addrSocket} connected.")
        connected = True
        while connected:
            try:
                rawMessage = connSocket.recv(self.BUFFER_SIZE)

                if not len(rawMessage):
                    connSocket.close()
                    continue

                parsedMessage = rawMessage.decode(self.FORMAT)

                request = Request(parsedMessage)

                if request.HEADERS['METHOD'] == 'GET':
                    response = self.HandleGetMethod(request)
                elif request.HEADERS['METHOD'] == 'POST':
                    response = self.HandlePostMethod(request)
                elif request.HEADERS['METHOD'] == 'DELETE':
                    response = self.HandleDeleteMethod(request)

                if request.COOKIES.get('__session') == None:
                    sessionId = uuid.uuid4()
                    file = open(os.path.join('sessions', str(sessionId)), 'x')
                    file.close()
                    response.SetCookie('__session', str(sessionId), 60 * 2)

                self.SendResponse(connSocket, response)
                connected = False
                connSocket.close()
            except IOError:
                response = Response().NotFound()

                self.SendResponse(connSocket, response)
                connected = False
                connSocket.close()
    
    def SendResponse(self, connectionSocket: socket.socket, response: Response) -> None:
        result: str = response.HEADERS['PROTOCOL'] + ' ' + response.HEADERS['STATUS_CODE'] + ' ' + response.HEADERS['STATUS_MESSAGE'] + '\r\n'
        
        for header, value in response.HEADERS.items():
            if header == 'PROTOCOL' or header == 'STATUS_CODE' or header == 'STATUS_MESSAGE' or header == 'body':
                continue

            result += header + ': ' + value + '\r\n'
        
        for _, cookie in response.COOKIES.items():
            result += 'Set-cookie: ' + cookie['key'] + '=' + cookie['value'] + '; '
            result += 'Domain=' + self.SERVER_IP + '; '
            result += 'Path=/; '

            if cookie['ttl'] is not None and cookie['ttl'] != '':
                result += 'Expires=' + cookie['ttl'] + '; '
            
            result += '\r\n'

        result += '\r\n'

        connectionSocket.send(result.encode(self.FORMAT))

        if response.BODY is None:
            if response.HEADERS['STATUS_CODE'] == '404':
                filePath = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, '404.html')
                response.Content(filePath, '.html', self.FORMAT)
            elif response.HEADERS['STATUS_CODE'] == '401':
                filePath = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, '401.html')
                response.Content(filePath, '.html', self.FORMAT)

        if response.BODY is not None:
            try:
                body = response.BODY.encode(self.FORMAT)
            except (UnicodeDecodeError, AttributeError):
                body = response.BODY

            # Calculo quantos pacotes são necessários a partir do tamanho do documento
            packages = math.ceil(len(body) / self.BUFFER_SIZE)

            for package in range(packages):
                start = package * self.BUFFER_SIZE
                end = start + self.BUFFER_SIZE
                connectionSocket.send(body[start: end])
    
    def HandleGetMethod(self, request: Request) -> Response:
        _, extension = os.path.splitext(request.HEADERS['PATH'])
        isValidObject = re.search('\.(html|js|css|svg|png|jpg|jpeg|ico)', extension)
        paths = request.HEADERS['PATH'].split('/')

        if isValidObject == None:
            # Se a última string após a última '/' for um diretorio, ou estiver na home
            # Ex: /teste -> Se 'teste' for um diretório
            if os.path.isdir(paths[len(paths) - 1]) or request.HEADERS['PATH'] == '/':
                return self.TryGetIndexFile(request)
            else:
                return Response().NotFound()
        
        filePath = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, *paths)

        if request.HEADERS['PATH'] == '/privado.html':
            isLogged = request.GetSessionKey('loggedin', False)
            if isLogged == True:
                return Response().Succesfull().Content(filePath, extension, self.FORMAT)
            else:
                return Response().Redirect(to='/')    
        
        if os.path.exists(filePath):
            return Response().Succesfull().Content(filePath, extension, self.FORMAT)
        else:
            return Response().NotFound()           
    
    def TryGetIndexFile(self, request: Request) -> Response:
        filePath = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, *request.HEADERS['PATH'].split('/'), 'index.html')
        
        if os.path.exists(filePath):
            return Response().Succesfull().Content(filePath, '.html', self.FORMAT)
        else:
            return Response().NotFound()
    
    def HandlePostMethod(self, request: Request) -> Response:
        if request.HEADERS['PATH'] == '/submit':
            return LoginController().Submit(request)
        
    def HandleDeleteMethod(self, request: Request) -> Response:
        if request.HEADERS['PATH'] == '/logout':
            request.SetSessionValue('loggedin', False)
            return Response().Redirect(to='/')
            