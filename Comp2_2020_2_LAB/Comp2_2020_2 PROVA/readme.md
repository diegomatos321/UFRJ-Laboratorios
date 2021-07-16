# Prova 2020.02 Comp2
## Enunciado da prova:

1) Baixe o projeto Biblioteca que se encontra no GitHub.
2) Faça os testes passarem (a maior quantidade que você puder), sem modificar a classe de teste.
3) Envie seu código por email com o assunto "[Comp2_2020_2] PROVA -- Aluno(a): Seu Nome Completo"e;.
4) Explique, no corpo do e-mail, e sem necessidade de escrever código, que tipo de alteração você faria se quisesse fazer com que usuários fossem categorizados como INICIANTE, EXPERIENTE ou ILIMITADO, com um número mínimo de livros devolvidos para passar de um nível para o outro, e fazendo com que a quantidade máxima de livros emprestados ao mesmo tempo para um usuário fosee função de sua categoria.
   1) Primeiramente, criaria um novo atributo "nivel" do tipo String no usuário e os devidos getters e setters para o novo atributo. 
   2) Através da biblioteca, criaria um método com parâmetros Usuario e o nivel, responsável por alterar o nível do usuário. Sempre que esse método fosse chamado, o nivel do usuário seria escolhido através de um Enum previamente criado. 
   3) No Enum, teríamos como atributos a quantidade mínima de livros a serem devolvidos para passar de um nível para outro. Então, dentro do método "receberDevolucaoLivro" verificaríamos se a meta foi atingida, se sim, subir para o nível apropriado. 
   4) Finalmente, retiraria o atributo "usuarioByLivrosDevolvidos" e colocaria a ArrayList de "livrosDevolvidos" como atributo do usuário, implementando os métodos apropriados(getters, setters e "usuarioPossui")
5) Explique, no corpo do e-mail, e sem necessidade de escrever código, que tipo de alteração você faria se quisesse permitir que sua biblioteca emprestasse também jogos, revistas e DVDs.
   1) Criaria um novo objeto "Emprestavel" e alteraria a Biblioteca para receber Objetos do tipo "Emprestavel". Agora, todos os objetos que forem passados como parâmetros tem que ser "emprestáveis". Feito isso, basta herdar nos objetos que quero emprestar, como Livros, jogos, revistas, DVDs... do msm objeto "Emprestavel"
6) Explique, no corpo do e-mail, e sem necessidade de escrever código, que tipo de alteração você faria se quisesse permitir que certas instâncias de Biblioteca pudessem emprestar apenas livros, ou apenas jogos, ou apenas revistas, ou apenas DVDs.
   1) Implementaria um tipo genérico na Biblioteca que receberia um Emprestável, dessa forma, basta herdar nos objetos que quero "emprestar" de emprestável, como livros, jogos, revistas, DVDs... e faria as devidas alterações

Cada teste vale 0,5 pontos. Cada uma das questões descritas nos itens 4, 5 e 6 acima vale 1,0 ponto. Entrega por e-mail até as 10:10 da manhã do dia 07/06/21.