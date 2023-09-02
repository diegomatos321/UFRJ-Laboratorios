import socket

SERVER_PORT = 3000
FORMAT = 'utf-8'
SERVER_IP = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER_IP, SERVER_PORT)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

print("[STARTING] Server is starting...")
server.listen(1)

while True:
    print(f"[LISTENING] Server is listening on {SERVER_IP}")

    connectionSocket, addr = server.accept()
    print(f"[NEW CONNECTION] {addr} connected.")

    try:
        rawMessage = connectionSocket.recv(1024)
        message = rawMessage.decode(FORMAT)
        response = message.upper()
        connectionSocket.send(response.encode(FORMAT))
    except IOError:
        connectionSocket.close()

server.close()
        