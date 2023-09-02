import socket

SERVER_PORT = 3000
FORMAT = 'utf-8'
SERVER_IP = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER_IP, SERVER_PORT)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)

request = "Hello World"
client.send(request.encode(FORMAT))
rawResponse = client.recv(1024)
response = rawResponse.decode(FORMAT)
print(response)