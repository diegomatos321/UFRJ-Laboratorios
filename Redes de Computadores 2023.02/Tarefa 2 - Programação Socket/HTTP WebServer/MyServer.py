import socket
import math
import re
import os

class MyServer:
    FORMAT: str = 'ascii'
    BUFFER_SIZE: int = 4096
    PUBLIC_PATH: str = 'public'
    SERVER_IP: str|None = None
    SERVER_PORT: int|None = None
    SERVER_PATH: str = ''

    def __init__(self) -> None:
        self.SERVER_PATH = os.path.dirname(__file__)
        pass

    def Listen(self, server_port: int, server_ip: str|None = None) -> None:
        self.SERVER_PORT = server_port

        if server_ip is None:
            self.SERVER_IP = socket.gethostbyname(socket.gethostname())
        else:
            self.SERVER_IP = server_ip

        ADRR = (self.SERVER_IP, self.SERVER_PORT)

        self.SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.SERVER.bind(ADRR)

        print("[STARTING] Server is starting...")
        self.SERVER.listen(1)

        while True:
            print(f"[LISTENING] Server is listening on {self.SERVER_IP}:{self.SERVER_PORT}")

            connectionSocket, addr = self.SERVER.accept()
            print(f"[NEW CONNECTION] {addr} connected.")

            try:
                rawRequest = connectionSocket.recv(self.BUFFER_SIZE)

                if not len(rawRequest):
                    connectionSocket.close()
                    continue

                request = rawRequest.decode(self.FORMAT)
                
                lines = request.split("\r\n")
                METHOD, PATH, PROTOCOL = lines[0].split()

                #Get request headers
                REQUEST_HEADERS = {}
                REQUEST_HEADERS['METHOD'] = METHOD
                REQUEST_HEADERS['PATH'] = PATH
                REQUEST_HEADERS['PROTOCOL'] = PROTOCOL
                REQUEST_HEADERS['BODY'] = {}

                contador = 1
                for line in lines[1:]:
                    contador += 1
                    if line == '':
                        break

                    HEADER, VALUE = line.split(': ')
                    REQUEST_HEADERS[HEADER] = VALUE
                
                if contador < len(lines):
                    # O método GET retorna duas linhas em branco
                    # Verificando se a proxima não está em branco
                    if lines[contador] != '':
                        contents = lines[contador].split('&')
                        for content in contents:
                            KEY, VALUE = content.split('=')
                            REQUEST_HEADERS["BODY"][KEY] = VALUE
                    
                # RESPONSE_HEADERS FIXOS
                RESPONSE_HEADERS = {}
                RESPONSE_HEADERS['PROTOCOL'] = 'HTTP/1.1'
                RESPONSE_HEADERS['Connection'] = "close"

                #Handle method
                if REQUEST_HEADERS['METHOD'] == 'GET':
                    result = re.search('.*\.(html|ico)', REQUEST_HEADERS['PATH'])

                    if result == None:
                        filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, 'index.html')
                        if os.path.exists(filename):
                            body = open(filename).read()
                            
                            RESPONSE_HEADERS['STATUS_CODE'] = chr(200)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'OK'
                            RESPONSE_HEADERS['Content-Length'] = chr(len(body.encode(self.FORMAT)))
                            RESPONSE_HEADERS['Content-Type'] = 'text/html' #TODO Tipo do arquivo dinamico
                            RESPONSE_HEADERS['body'] = body
                        else:
                            RESPONSE_HEADERS['STATUS_CODE'] = str(404)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Not Found'
                    else:
                        paths = REQUEST_HEADERS['PATH'].split('/')
                        filename = os.path.join(self.SERVER_PATH, self.PUBLIC_PATH, *paths)
                        
                        if os.path.exists(filename):
                            body = open(filename).read()
                            
                            RESPONSE_HEADERS['STATUS_CODE'] = ord(200)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'OK'
                            RESPONSE_HEADERS['Content-Length'] = ord(len(body.encode(self.FORMAT)))
                            RESPONSE_HEADERS['Content-Type'] = 'text/html' #TODO Tipo do arquivo dinamico
                            RESPONSE_HEADERS['body'] = body
                        else:
                            RESPONSE_HEADERS['STATUS_CODE'] = str(404)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Not Found'
                elif REQUEST_HEADERS['METHOD'] == 'POST':
                    if REQUEST_HEADERS['PATH'] == '/submit':
                        if REQUEST_HEADERS['BODY']['nome'] == 'Diego' and REQUEST_HEADERS['BODY']['senha'] == '123456':
                            RESPONSE_HEADERS['STATUS_CODE'] = str(301)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Moved Permanently'
                            RESPONSE_HEADERS['Content-Type'] = 'text/html' #TODO Tipo do arquivo dinamico
                            RESPONSE_HEADERS['Location'] = 'pagina.html'
                        else:
                            RESPONSE_HEADERS['STATUS_CODE'] = str(404)
                            RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Not Found'

                self.SendResponse(connectionSocket, RESPONSE_HEADERS)
                connectionSocket.close()
            except IOError:
                connectionSocket.close()

    def SendResponse(self, connectionSocket: socket, RESPONSE_HEADERS: dict):
        response = RESPONSE_HEADERS['PROTOCOL'] + ' ' + RESPONSE_HEADERS['STATUS_CODE'] + ' ' + RESPONSE_HEADERS['STATUS_MESSAGE'] + '\r\n'
        
        for header, value in RESPONSE_HEADERS.items():
            if header == 'PROTOCOL' or header == 'STATUS_CODE' or header == 'STATUS_MESSAGE' or header == 'body':
                continue

            response += header + ': ' + value + '\r\n'
        response += '\r\n'

        connectionSocket.send(response.encode(self.FORMAT))

        if RESPONSE_HEADERS.get('body') is not None:
            body = RESPONSE_HEADERS['body'].encode(self.FORMAT)

            # Calculo quantos pacotes são necessários a partir do tamanho do documento
            packages = math.ceil(len(body) / self.BUFFER_SIZE)

            for package in range(packages):
                start = package * self.BUFFER_SIZE
                end = start + self.BUFFER_SIZE
                connectionSocket.send(body[start: end])