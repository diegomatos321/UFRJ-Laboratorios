import socket
import sys

HOST = "127.0.0.1"
PORT = 5000

def main():
    # Lê todos os bytes da entrada padrão
    data = sys.stdin.buffer.read()

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((HOST, PORT))
    print("[CLIENTE] Conectado ao servidor.")

    client.sendall(data)
    client.close()
    print("[CLIENTE] Arquivo enviado (sem TLS).")

if __name__ == "__main__":
    main()
