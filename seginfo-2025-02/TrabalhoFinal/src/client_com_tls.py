# client_tls.py
import socket
import ssl
import sys

HOST = "127.0.0.1"
PORT = 5001

def main():
    # Lê todos os bytes da entrada padrão
    data = sys.stdin.buffer.read()

    context = ssl.create_default_context()
    context.check_hostname = False
    context.verify_mode = ssl.CERT_NONE  # aceitar certificado autoassinado

    raw_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    secure_sock = context.wrap_socket(raw_sock, server_hostname=HOST)

    secure_sock.connect((HOST, PORT))
    print("[CLIENTE TLS] Conexão segura estabelecida.")

    secure_sock.sendall(data)
    secure_sock.close()
    print("[CLIENTE TLS] Arquivo enviado com TLS.")

if __name__ == "__main__":
    main()
