import socket
import os
from uniquify import uniquify

HOST = "0.0.0.0"
PORT = 5000

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(1)

    print(f"[SERVIDOR] Aguardando conexão em {HOST}:{PORT}...")

    while True:
        conn, addr = server.accept()
        print(f"[SERVIDOR] Conexão estabelecida com {addr}")

        # Cria o diretório caso ele não exista
        os.makedirs('./out', exist_ok=True)

        with conn:
            filepath = uniquify("./out/recebido_sem_tls.txt")
            with open(filepath, "wb") as f:
                while True:
                    data = conn.recv(4096)
                    if not data:
                        break
                    f.write(data)

        print("[SERVIDOR] Arquivo recebido com sucesso.")

if __name__ == "__main__":
    main()
