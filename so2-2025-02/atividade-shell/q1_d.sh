#!/bin/bash

echo "=================================="
echo "     INFORMAÇÕES DO SISTEMA"
echo "=================================="
echo

# Mostrar horário atual
echo ">> Obtendo horário atual..."
date
echo "Pressione qualquer tecla para continuar..."
read c 
echo

# Mostrar tempo de atividade
echo ">> Verificando tempo de atividade do sistema..."
uptime
echo "Pressione qualquer tecla para continuar..."
read c

# Mostrar ocupação do disco
echo ">> Verificando ocupação do disco..."
df -h
echo "Pressione qualquer tecla para continuar..."
read c

# Mostrar usuários logados
echo ">> Listando usuários logados..."
who
echo "Pressione qualquer tecla para continuar..."
read c

echo ">> Exibindo resumo rápido de usuários..."
users
echo "Pressione qualquer tecla para continuar..."
read c

