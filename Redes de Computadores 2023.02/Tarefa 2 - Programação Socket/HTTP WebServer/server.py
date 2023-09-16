import socket
import math
import re
import os

SERVER_PORT = 8080
SERVER_IP = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER_IP, SERVER_PORT)
FORMAT = 'ASCII'
BUFFER_SIZE = 4096
PUBLIC_PATH = 'public'

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

print("[STARTING] Server is starting...")
server.listen(5)

def SendResponse(connectionSocket, RESPONSE_HEADERS):
    response = RESPONSE_HEADERS['PROTOCOL'] + ' ' + RESPONSE_HEADERS['STATUS_CODE'] + ' ' + RESPONSE_HEADERS['STATUS_MESSAGE'] + '\r\n'
    
    for header, value in RESPONSE_HEADERS.items():
        if header == 'PROTOCOL' or header == 'STATUS_CODE' or header == 'STATUS_MESSAGE' or header == 'body':
            continue

        response += header + ': ' + value + '\r\n'
    response += '\r\n'

    connectionSocket.send(response.encode(FORMAT))

    if RESPONSE_HEADERS.get('body') is not None:
        body = RESPONSE_HEADERS['body'].encode(FORMAT)

        # Calculo quantos pacotes são necessários a partir do tamanho do documento
        packages = math.ceil(len(body) / BUFFER_SIZE)

        for package in range(packages):
            start = package * BUFFER_SIZE
            end = start + BUFFER_SIZE
            connectionSocket.send(body[start: end])

while True:
    print(f"[LISTENING] Server is listening on {SERVER_IP}")

    connectionSocket, addr = server.accept()
    print(f"[NEW CONNECTION] {addr} connected.")

    try:
        rawRequest = connectionSocket.recv(BUFFER_SIZE)

        if not len(rawRequest):
            connectionSocket.close()
            continue

        request = rawRequest.decode(FORMAT)
        
        #Get request headers
        REQUEST_HEADERS = {}
        RESPONSE_HEADERS = {}

        # RESPONSE_HEADERS FIXOS
        RESPONSE_HEADERS['PROTOCOL'] = 'HTTP/1.1'
        RESPONSE_HEADERS['Connection'] = "close"

        lines = request.split("\r\n")

        METHOD, PATH, PROTOCOL = lines[0].split()
        REQUEST_HEADERS['METHOD'] = METHOD
        REQUEST_HEADERS['PATH'] = PATH
        REQUEST_HEADERS['PROTOCOL'] = PROTOCOL

        for line in lines[1:]:
            if not len(line):
                continue

            HEADER, VALUE = line.split(': ')
            REQUEST_HEADERS[HEADER] = VALUE

        #Handle method
        if REQUEST_HEADERS['METHOD'] == 'GET':
            result = re.search('.*\.(html|ico)', REQUEST_HEADERS['PATH'])

            if result == None:
                filename = PUBLIC_PATH + '/index.html'
                if os.path.exists(filename):
                    body = open(filename).read()
                    
                    RESPONSE_HEADERS['STATUS_CODE'] = str(200)
                    RESPONSE_HEADERS['STATUS_MESSAGE'] = 'OK'
                    RESPONSE_HEADERS['Content-Length'] = str(len(body.encode(FORMAT)))
                    RESPONSE_HEADERS['Content-Type'] = 'text/html' #TODO Tipo do arquivo dinamico
                    RESPONSE_HEADERS['body'] = body
                else:
                    RESPONSE_HEADERS['STATUS_CODE'] = str(404)
                    RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Not Found'
            else:
                filename = PUBLIC_PATH + REQUEST_HEADERS['PATH']
                
                if os.path.exists(filename):
                    body = open(filename).read()
                    
                    RESPONSE_HEADERS['STATUS_CODE'] = str(200)
                    RESPONSE_HEADERS['STATUS_MESSAGE'] = 'OK'
                    RESPONSE_HEADERS['Content-Length'] = str(len(body.encode(FORMAT)))
                    RESPONSE_HEADERS['Content-Type'] = 'text/html' #TODO Tipo do arquivo dinamico
                    RESPONSE_HEADERS['body'] = body
                else:
                    RESPONSE_HEADERS['STATUS_CODE'] = str(404)
                    RESPONSE_HEADERS['STATUS_MESSAGE'] = 'Not Found'
        
        SendResponse(connectionSocket, RESPONSE_HEADERS)
        connectionSocket.close()
    except IOError:
        connectionSocket.close()


