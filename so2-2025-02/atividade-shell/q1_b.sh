#!/bin/bash

echo ">> Obtendo horário atual..."
date
echo

echo ">> Verificando tempo de atividade do sistema..."
uptime
echo

echo ">> Verificando ocupação do disco..."
df -h
echo

echo ">> Listando usuários logados..."
who
echo

echo ">> Exibindo resumo rápido de usuários..."
users
echo
