#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int i;
    double a;
    int intervalos[4][2] = {
        {0, 25},
        {25, 50},
        {50, 75},
        {75, 100}};

    scanf("%lf", &a);

    if (a < intervalos[0][0] || a > intervalos[3][1])
    {
        printf("Fora de intervalo");
        exit(1);
    }

    for (i = 0; i < 4; i++)
    {
        const int *intervalo = intervalos[i];

        if (i == 0)
        {
            if (a >= intervalo[0] && a <= intervalo[1])
            {
                printf("Intervalo [%i,%i]\n", intervalo[0], intervalo[1]);
                break;
            }
        }

        if (a > intervalo[0] && a <= intervalo[1])
        {
            printf("Intervalo (%i,%i]\n", intervalo[0], intervalo[1]);
            break;
        }
    }

    return 0;
}
