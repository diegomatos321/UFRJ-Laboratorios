# Tarefa 5 Compiladores 2025-1

Aluno: Diego Vasconcelos Schardosim de Matos
DRE: 120098723

## Como usar

O trabalho é divido em duas partes:
1. O programa compilador.lua irá realizar a análise léxica, depois irá realizar a análise sintática, por fim, irá escrever o bytecode na saída padrão, ex:
    lua compilador.lua < entrada.txt > saida.bytecode

Caso deseje imprimir os tokens e a árvore abstrata use o argumento -d ou --debug, ex:
    lua compilador.lua -d < entrada.txt > saida.txt

O compilador.lua também aceita ser executado em modo interpretador com o argumento -i ou --interpreter (por motivos de força maior está fixado como segundo argumento)
    lua compilador.lua -d -i < entrada.txt > saida.txt

2. O programa vm.lua recebe como primeiro argumento o caminho do arquivo bytecode e executa o programa, simulando um máquina de pilha
    lua vm.lua entrada.bytecode

A vm atualmente aceita:
- tipos primitivos como: string, inteiros, floats, booleanos
- construtores de tabelas
- comandos de atribuição, ifs, whiles, ~~local, chamada de função~~
~~- declaração de funções do usuário e funções anônimas~~
- função nativa print 
~~- funções anônimas~~
~~- acesso a tabelas com notação de pontinho: "t.campo"~~
- construtores de tabela array: {10,20,30}
- construtores de tabela chave-valor: {x=10, y=20}
