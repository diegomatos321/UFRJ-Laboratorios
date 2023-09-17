import socket
import math
import re
import os
from Request import Request
from Response import Response

class MyServer:
    FORMAT: str = 'UTF-8'
    BUFFER_SIZE: int = 4096
    PUBLIC_PATH: str = 'public'
    SERVER_IP: str|None = None
    SERVER_PORT: int|None = None
    SERVER_PATH: str = ''

    def __init__(self) -> None:
        self.SERVER_PATH = os.path.dirname(__file__)
        pass

    def Listen(self, server_port: int, server_ip: str|None = None) -> None:
        self.Bootstrap(server_port, server_ip)

        print("[STARTING] Server is starting...")
        self.SERVER.listen(1)

        while True:
            print(f"[LISTENING] Server is listening on {self.SERVER_IP}:{self.SERVER_PORT}")

            connectionSocket, addr = self.SERVER.accept()
            print(f"[NEW CONNECTION] {addr} connected.")

            try:
                rawMessage = connectionSocket.recv(self.BUFFER_SIZE)

                if not len(rawMessage):
                    connectionSocket.close()
                    continue

                parsedMessage = rawMessage.decode(self.FORMAT)

                request = Request(parsedMessage)
                
                if request.HEADERS['METHOD'] == 'GET':
                    response = self.HandleGetMethod(request)
                elif request.HEADERS['METHOD'] == 'POST':
                    response = self.HandlePostMethod(request)

                self.SendResponse(connectionSocket, response)
                connectionSocket.close()
            except IOError:
                response = Response().NotFound()
                
                self.SendResponse(connectionSocket, response)
                connectionSocket.close()

    def Bootstrap(self, server_port:int, server_ip: str|None = None) -> None:
        self.SERVER_PORT = server_port

        if server_ip is None:
            self.SERVER_IP = socket.gethostbyname(socket.gethostname())
        else:
            self.SERVER_IP = server_ip

        ADRR = (self.SERVER_IP, self.SERVER_PORT)

        self.SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.SERVER.bind(ADRR)

    def SendResponse(self, connectionSocket: socket.socket, response: Response) -> None:
        result: str = response.HEADERS['PROTOCOL'] + ' ' + response.HEADERS['STATUS_CODE'] + ' ' + response.HEADERS['STATUS_MESSAGE'] + '\r\n'
        
        for header, value in response.HEADERS.items():
            if header == 'PROTOCOL' or header == 'STATUS_CODE' or header == 'STATUS_MESSAGE' or header == 'body':
                continue

            result += header + ': ' + value + '\r\n'
        result += '\r\n'

        connectionSocket.send(result.encode(self.FORMAT))

        if response.BODY is None:
            if response.HEADERS['STATUS_CODE'] == '404':
                filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, '404.html')
                response.BODY = open(filename).read()
            elif response.HEADERS['STATUS_CODE'] == '401':
                filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, '401.html')
                response.BODY = open(filename).read()

        if response.BODY is not None:
            body = response.BODY.encode(self.FORMAT)

            # Calculo quantos pacotes são necessários a partir do tamanho do documento
            packages = math.ceil(len(body) / self.BUFFER_SIZE)

            for package in range(packages):
                start = package * self.BUFFER_SIZE
                end = start + self.BUFFER_SIZE
                connectionSocket.send(body[start: end])
    
    def HandleGetMethod(self, request: Request) -> Response:
        isValidObject = re.search('.*\.(html|ico)', request.HEADERS['PATH'])

        if isValidObject == None:
            return self.TryGetIndexFile(request)
        
        paths = request.HEADERS['PATH'].split('/')
        filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, *paths)
        
        if os.path.exists(filename):
            return Response().Succesfull().View(filename)
        else:
            return Response().NotFound()           
    
    def TryGetIndexFile(self, request: Request) -> Response:
        filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, 'index.html')
        
        if os.path.exists(filename):
            return Response().Succesfull().View(filename, self.FORMAT)
        else:
            return Response().NotFound()
    
    def HandlePostMethod(self, request: Request) -> Response:
        if request.HEADERS['PATH'] == '/submit':
            if request.BODY['nome'] == 'Diego' and request.BODY['senha'] == '123456':
                return Response().Redirect(to='pagina.html')
            else:
                return Response().Unauthorized()