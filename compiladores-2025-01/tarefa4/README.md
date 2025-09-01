# Tarefa 3 Compiladores 2025-1

Aluno: Diego Vasconcelos Schardosim de Matos
DRE: 120098723

## Como usar

O programa realiza leitura da entrada padrão de um programa lua e escrita na saída padrão, basta chamar como:

lua compilador.lua < entrada.txt > saida.txt

Ele irá realizar a análise léxica, depois irá realizar a análise sintática, por fim, irá interpretar o programa de entrada. Caso deseje imprimir os tokens e a árvore abstrata use o argumento -d ou --debug, ex:

lua compilador.lua -d < entrada.txt > saida.txt

Aceita:
- tipos primitivos como: string, inteiros, floats, booleanos
- construtores de tabelas
- comandos de atribuição, ifs, whiles, local, chamada de função
- declaração de funções do usuário e funções anônimas
- função nativa print 
- funções anônimas
- acesso a tabelas com notação de pontinho: "t.campo"
- construtores de tabela array: {10,20,30}
- construtores de tabela chave-valor: {x=10, y=20}
