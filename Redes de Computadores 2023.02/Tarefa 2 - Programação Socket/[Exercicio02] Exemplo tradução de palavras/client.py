import socket
import os

SERVER_PORT = 3000
FORMAT = 'utf-8'
SERVER_IP = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER_IP, SERVER_PORT)
BUFFER_SIZE = 4096
INVALID_MESSAGE = 'Escolha inválida'

while True:
    if os.name == 'nt':
        os.system('cls')
    else:
        os.system('clear')
    
    print('''
        === Seja bem vindo a essa aplicação de teste ===
        Minha função é traduzir palavras-chaves sobre Redes de Computadores para outro idioma
        Escolha uma das opções abaixo:
        (1) Inglês
        (2) Francês
        (3) Sair
    ''')

    choice = input()

    if choice == "3":
        print("Até logo")
        break

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)

    if choice == "1":
        client.send(choice.encode(FORMAT))

        rawResponse = client.recv(BUFFER_SIZE)
        response = rawResponse.decode(FORMAT)
        print(f"Você selecionou a opção Inglês\nDigite uma palavra para ser traduzida, as opções são: {response}")
    elif choice == "2":
        client.send(choice.encode(FORMAT))

        rawResponse = client.recv(BUFFER_SIZE)
        response = rawResponse.decode(FORMAT)
        print(f"Você selecionou a opção Francês\nDigite uma palavra para ser traduzida, as opções são: {response}")
    else:
        print("Opção Inválida, digite novamente")
        client.close()
        continue

    while True:
        request = input()

        if request == '3':
            print("Até logo")
            client.close()
            break

        client.send(request.encode(FORMAT))
        rawResponse = client.recv(BUFFER_SIZE)
        response = rawResponse.decode(FORMAT)

        if response == INVALID_MESSAGE:
            print("Palavra não encontrada, digite novamente")
            continue

        print(response)
    
exit()