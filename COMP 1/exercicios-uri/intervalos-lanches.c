#include <stdio.h>

struct Lanche
{
    unsigned int codigo;
    char nome[50];
    float preco;
};

int main()
{
    unsigned int quantidade, codigo, i;
    float precoTotal, precoLanche;
    struct Lanche lanches[5] = {
        {1,
         "Cachorro Quente",
         4.0},
        {2,
         "X-Salada",
         4.5},
        {3,
         "X-Bacon",
         5.0},
        {4,
         "Torrada Simples",
         2.0},
        {5,
         "Refrigerante",
         1.5}};

    scanf("%u %u", &codigo, &quantidade);

    for (i = 0; i < 5; i++)
    {
        const struct Lanche lanche = lanches[i];

        if (lanche.codigo == codigo)
        {
            precoLanche = lanche.preco;
        }
    }

    precoTotal = precoLanche * quantidade;

    printf("Total: R$ %.2f\n", precoTotal);

    return 0;
}