import socket
import ssl
from uniquify import uniquify

HOST = "0.0.0.0"
PORT = 5001

def main():
    # carregando certificado e chave
    context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    context.load_cert_chain(certfile="cert.pem", keyfile="key.pem")

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(1)

    print(f"[SERVIDOR TLS] Aguardando conexão segura em {HOST}:{PORT}...")

    while True:
        conn, addr = server.accept()
        secure_conn = context.wrap_socket(conn, server_side=True)
        print(f"[SERVIDOR TLS] Conexão TLS com {addr}")

        with secure_conn:
            filepath = uniquify("./out/recebido_com_tls.txt")
            with open(filepath, "wb") as f:
                while True:
                    data = secure_conn.recv(4096)
                    if not data:
                        break
                    f.write(data)

        print("[SERVIDOR TLS] Arquivo recebido com criptografia.")

if __name__ == "__main__":
    main()
