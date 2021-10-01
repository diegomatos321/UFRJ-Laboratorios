# Pseudo Código, em linguagem natural, para os algoritmos da Prática 1
_Dúvidas e perguntas no final do documento._  
_Repositório: https://github.com/diegomatos321/Linguagem-C-Pratica_
## Exercício 1 
### 1. Escreva a representação de um algoritmo de cálculo da média de dois números quaisquer.

1. Enquanto a tarefa não for resolvida, eu devo:
   1. Perguntar o primeiro número.
   2. Anotar o primeiro número.
   3. Perguntar o segundo número.
   4. Anotar o segundo número.
   5. Calcular a média aritmética de ambos os números.
      1. Somar todos os elementos.
      2. Anotar a soma.
      3. Realizar a razão entre a soma e a quantidade de elementos.
   6. Mostrar a média para o usuário.
   7. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   8. Volte para o início.

### 2.Escreva a representação de um algoritmo que calcule as raizes x1 e x2 de uma equação de segundo grau.

1. Enquanto a tarefa não for resolvida, eu devo:
   1. Perguntar qual é a equação do 2º Grau a se calcular.
   2. Anotar equação.
   3. Confirmar se a equação recebida é a desejada.
   4. Se sim, logo:
      1. A equação deve pertencer aos números reais.
      2. Verificar se o coeficiente "a" é válido.
         1. Se não for, mostrar uma mensagem de erro e volte para o início.
      3. Calcular Delta.
      4. Anotar delta.
      5. Verificar se Delta é maior ou igual a zero.
         1. Se não for, mostrar uma mensagem de erro e volte para o início.
      6. Encontrar as raízes através da fórmula de Bhaskara.
      7. Mostrar as Raízes.
      8. Perguntar se deseja refazer o Algoritmo.
         1. Se não, tarefa resolvida.
      9. Volte para o início.
   5. Se não, volte para o início.

### 3. Escreva a representação de um algoritmo que dada a idade de um espectador, informe se ele tem permissão para meia-entrada por ser idoso ou não. Considere que a pessoa é idosa se tiver mais de 60 anos. 

1. Enquanto a tarefa não for resolvida, eu devo:
   1. Perguntar a idade o espectador.
   2. Anotar idade.
   3. Se idade for maior que 60 anos, eu devo:
      1. Requisitar que pague meia-entrada
   4. Se não:
      1. Deve pagar a entrada inteira.
   5. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   6. Volte para o início.

## Exercício 2
### 1. Fazer um programa que imprima a média aritmética dos números 7, 8 e 9 e a média dos números 4, 5 e 6. Depois este mesmo programa deve calcular a soma das duas médias e a médias dessas médias calculadas, mostrando o resultado para o usuário.

1. Definir primeira lista de números.
2. Definir segunda lista de números.
3. Definir média aritmética:
   1. Razão da soma dos elementos pela quantidade de elementos.
4. Calcular a média aritmética entre os números da primeira lista.
5. Anotar média.
6. Calcular média aritmética entre os números da segunda lista.
7. Anotar média.
8. Somar as médias da primeira lista e da segunda lista.
9. Anotar a soma dasa médias.
10. Mostrar a soma das médias.
    
### 2. Criar um programa que calcule o juros pelo atraso de um pagamento, recebendo o valor de juros que é cobrado por mês de atraso, a quantidade de meses de atraso e o valor original do valor a ser pago.

1. Definir Juros Simples:
   1. Perguntar a taxa de juros.
   2. Anotar taxa de juros.
   3. Perguntar o Capital inicial.
   4. Anotar Capital inicial.
   5. Perguntar o período de capitalização.
   6. Anotar período de capitalização.
   7. Juros é definido pelo produto entre Capital inicial, taxa de juros e período.
   8. Calcular Juros.
   9. Anotar Juros.
   10. Apresentar quantidade de juros.
   11. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   12. Volte para o início.
2. Definir Juros Compostos:
   1. Perguntar a taxa de juros.
   2. Anotar taxa de juros.
   3. Perguntar o Capital inicial.
   4. Anotar Capital inicial.
   5. Perguntar o período de capitalização.
   6. Anotar período de capitalização.
   7. Montante é definido pelo produto entre Capital inicial e a soma da taxa de juros somada a um elevado à potencia igual ao periodo de capitalização
   8. Calcular Montande.
   9. Anotar Montante.
   10. Juros é definido pela diferença entre o montante e o capital inicial.
   11. Calcular Juros.
   12. Anotar Juros.
   13. Apresentar quantidade de juros.
   14. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   15. Volte para o início.
3. Enquanto o exercicio não for resolvido:
   1. Apresentar opções de calculo: Juros Simples ou Composto.
   2. Perguntar escolha.
   3. Anotar escolha.
   4. Se escolha for igual a Juros Simples, então:
      1. Calcular Juros Simples;
   5. Se não, é igual à Juros Compostos, então:
      1. Calcular Juros Compostos.
   6. Se não:
      1. Apresentar mensagem de erro.
      2. Volte ao início.

### 3. Leia um número. Se ele for positivo, imprimir a raiz quadrada, senão exibir uma mensagem de que não é possível calcular a raiz.

1. Enquanto a tarefa não for resolvida, eu devo:
   1. Perguntar um número qualquer.
   2. Anotar o número.
   3. Verificar se o número é negativo.
      1. Se for, mostrar uma mensagem de erro e voltar para o início.
   4. Realizar a raiz quadrada.
   5. Anotar raiz quadrada.
   6. Apresentar a raiz quadrada.
   7. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   8. Volte para o início.

### 4. Crie um algoritmo que receba 3 números e informe qual o maior entre eles.

1. Definir Encontrar Maior Número:
   1. Percorrer pela lista de numeros
      1. Se o numero atual for maior que o candidato a maior numero, então:
         1. Numero atual é o candidato a maior número
2. Enquanto tarefa não for resolvida, eu devo:
   1. Repetir 3 vezes:
      1. Perguntar número.
      2. Anotar número na lista.
   2. Encontrar maior número da lista.
   3. Apresentar o maior número.
   4. Perguntar se ele deseja refazer o Algoritmo.
      1. Se não, tarefa resolvida.
   5. Volte para o início.

### 5. Faça um algoritmo que leia dois números e indique se são iguais ou se são diferentes. Mostre o maior e o menor (nesta sequência).

1. Enquanto tarefa não for resolvida, eu devo:
   1. Perguntar primeiro número.
   2. Anotar primeiro número
   3. Perguntar segundo número.
   4. Anotar segundo número.
   5. Se primeiro número for igual ao segundo número, então:
      1. Mostrar que são iguais
   6. Se não, então:
      1. Mostrar que são diferentes
   7. Perguntar se deseja refazer o algoritmo.
      1. Se não, tarefa resolvida.
   8. Volte para o início.

## Dúvidas e Perguntas:
1. Criar uma função que retorne uma _Array_   
No exercício de número **1**, na linha 132, meu objetivo é criar uma função com única responsabilidade de calcular a fórmula de Bhaskara e que me retornaria uma Array contendo as raizes da função dada. 
Após uma pesquisa no Google eu tentei alocar, dinamicamente, na memória a lista e retornar ela para um ponteiro. Logo, quem chamasse a função poderia resgatar o ponteiro e usar os valores dele, **porém**, não esta funcionando.
Como devo fazer isso ?  
2. Soma das médias  
No exercício de número **2**, na linha 73, eu tento realizar a soma de dois inteiros, esses são retornados pela função `int calcularMediaEntreNumeros(int lista[]);`, entretando o compilador da um aviso dizendo: 
   ```C
      warning: assignment to 'int' from 'int *' makes integer from pointer without a cast [-Wint-conversion]
         73 |   somaDasMedias = primeiraLista + segundaMedia;
   ```  
   O que eu devo fazer ?
3. Como eu separo minhas funções em arquivos distintos ? (Importar e exportar elas)