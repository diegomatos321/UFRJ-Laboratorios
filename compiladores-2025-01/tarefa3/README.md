# Tarefa 1 Compiladores 2025-1

Aluno: Diego Vasconcelos Schardosim de Matos
DRE: 120098723

## Como usar

O programa realiza leitura da entrada padrão e escrita na saída padrão, basta chamar

lua compilador.lua < entrada.txt > saida.txt

Ele irá realizar a análise léxica e imprimir os token, depois irá realizar o parser e imprimir a árvore de sintaxe abstrata, por fim, irá interpretar a árvore

Aceita comandos de atribuição, ifs, whiles e tabelas além de:
- Acesso a tabelas com notação de pontinho: "t.campo"
- Construtores de tabela array: {10,20,30}
- Construtores de tabela chave-valor: {x=10, y=20}
