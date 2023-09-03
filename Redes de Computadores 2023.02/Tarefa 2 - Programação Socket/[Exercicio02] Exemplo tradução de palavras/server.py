import socket

SERVER_PORT = 3000
FORMAT = 'utf-8'
SERVER_IP = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER_IP, SERVER_PORT)
BUFFER_SIZE = 4096
INVALID_MESSAGE = 'Escolha inválida'

portToEnglish = {
    'enlace': 'link',
    'roteador': 'router',
    'pacote': 'packet',
    'rede': 'network',
    'protocolo': 'protocol',
    'hospedeiro': 'host',
    'mensagem': 'message',
    'propagação': 'propagation',
    'atraso': 'delay',
    'transmissão': 'transmission',
}

portToFrench = {
    'enlace': 'lien',
    'roteador': 'routeur',
    'pacote': 'paquet',
    'rede': 'réseau',
    'protocolo': 'protocole',
    'hospedeiro': 'hôte',
    'mensagem': 'message',
    'propagação': 'propagation',
    'atraso': 'retard',
    'transmissão': 'transmission',
}

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

print('[STARTING] Server is Starting...')
server.listen(1)

while True:
    print(f"[LISTENING] Server is listening on {SERVER_IP}")

    connectionSocket, addr = server.accept()
    print(f"[NEW CONNECTION] {addr} connected.")

    try:
        rawMessage = connectionSocket.recv(BUFFER_SIZE)
        message = rawMessage.decode(FORMAT)
        
        if message == "1":
            print(f"[CLIENT INPUT] Escolha {message}")
            dictionary = portToEnglish

            response = ""

            for word in list(dictionary.keys()):
                response += word + ', '

            connectionSocket.send(response.encode(FORMAT))
        elif message == "2":
            print(f"[CLIENT INPUT] Escolha {message}")
            dictionary = portToFrench

            response = ""

            for word in list(dictionary.keys()):
                response += word + ', '

            connectionSocket.send(response.encode(FORMAT))
        elif message == "3":
            connectionSocket.close()
            continue
        else:
            print(f"[{INVALID_MESSAGE}] {message}")
            connectionSocket.send(INVALID_MESSAGE.encode(FORMAT))
            connectionSocket.close()
            continue

        while True:
            rawMessage = connectionSocket.recv(BUFFER_SIZE)
            message = rawMessage.decode(FORMAT)
            print(f"[CLIENT INPUT] Palavra {message}")

            if message not in dictionary:
                connectionSocket.send(INVALID_MESSAGE.encode(FORMAT))
                continue

            connectionSocket.send(dictionary[message].encode(FORMAT))
        
        connectionSocket.close()
    except IOError:
        connectionSocket.close()

server.close()