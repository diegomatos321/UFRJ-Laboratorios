# Trabalho Final — Segurança da Informação (2025.02)

Aluno: Diego V. S. de Matos

DRE: 120098723

Este repositório contém a implementação e o relatório final do trabalho da disciplina de Segurança da Informação. O projeto está organizado da seguinte forma:

```
.
├── cert.pem
├── key.pem
├── out/            <- Saída gerada pelo servidor
├── readme.md
├── report/         <- Relatório e evidências
│   ├── captura-com-tls.png
│   ├── captura-sem-tls.png
│   ├── dados.csv
│   ├── relatorio.pdf
│   └── relatorio.tex
├── src/            <- Código fonte da implementação
│   ├── client_com_tls.py
│   ├── client_sem_tls.py
│   ├── server_com_tls.py
│   ├── server_sem_tls.py
│   └── uniquify.py
```

## Como executar a implementação

As execuções devem ser feitas a partir da raiz do projeto, garantindo que os arquivos de chave e certificado sejam localizados corretamente.

1) Teste sem TLS
Executar o servidor:
```python
python3 ./src/server_sem_tls.py
```
O servidor criará no diretório ./out/ uma cópia do arquivo enviado pelo cliente.

Executar o cliente:

O cliente recebe um arquivo via entrada padrão e o envia ao servidor.
```python
python3 ./src/client_sem_tls.py < arquivo.txt
```

2) Teste com TLS

O procedimento é semelhante ao teste sem TLS, porém utilizando os programas com suporte a TLS.

Executar o servidor:
```python
python3 ./src/server_com_tls.py
```

Executar o cliente:
```python
python3 ./src/client_com_tls.py < arquivo.txt
```

## Observação Importante

Todos os comandos devem ser executados a partir do diretório raiz do projeto.
Isso garante que os arquivos cert.pem e key.pem sejam encontrados corretamente pelos programas com TLS.