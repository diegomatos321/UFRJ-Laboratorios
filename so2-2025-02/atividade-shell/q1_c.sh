#!/bin/bash

echo ">> Obtendo horário atual..."
date
echo "Pressione qualquer tecla para continuar..."
read c 
echo


echo ">> Verificando tempo de atividade do sistema..."
uptime
echo "Pressione qualquer tecla para continuar..."
read c

echo ">> Verificando ocupação do disco..."
df -h
echo "Pressione qualquer tecla para continuar..."
read c

echo ">> Listando usuários logados..."
who
echo "Pressione qualquer tecla para continuar..."
read c

echo ">> Exibindo resumo rápido de usuários..."
users
echo "Pressione qualquer tecla para continuar..."
read c

