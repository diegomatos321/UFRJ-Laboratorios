#!/bin/bash
# Script para verificar se um arquivo existe e o tipo dele

# Pede o nome do arquivo
read -p "Digite o nome do arquivo ou diretório: " arquivo

# Verifica se o nome foi digitado
if [ -z "$arquivo" ]; then
    echo "Você não digitou nada! Encerrando o script."
    exit 1
fi

# Testa se o arquivo existe
if [ -e "$arquivo" ]; then
    echo
    echo "O caminho '$arquivo' existe."

    # Verifica se é arquivo ou diretório
    if [ -f "$arquivo" ]; then
        echo "É um arquivo comum."
    elif [ -d "$arquivo" ]; then
        echo "É um diretório."
    else
        echo "Existe, mas não é nem arquivo nem diretório (talvez um link, dispositivo, etc)."
    fi
else
    echo
    echo "O arquivo ou diretório '$arquivo' não existe."
fi

