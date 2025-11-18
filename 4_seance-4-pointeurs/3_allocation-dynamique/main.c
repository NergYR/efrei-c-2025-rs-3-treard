#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(void)
{
    printf("int : %llu\n", sizeof(int));
    printf("char : %llu\n", sizeof(char));
    printf("long : %llu\n", sizeof(long));
    printf("double : %llu\n", sizeof(double));
    printf("bool : %llu\n", sizeof(bool));
    return 0;
}

void dynamicTab()
{
    // Alloue dynamiquement de la memoire
    int * pta = malloc(sizeof(int));
    *pta = 10;

    // Alloue dynamiquement un tableau
    int * tab = malloc(sizeof(int) * 3);

    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;

    // Libere la memoire
    free(pta);
    free(tab);

    // tableau 2 D
    int ** tab2 = malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++)
    {
        tab2[i] = malloc(sizeof(int) * 4);
    }

    for (int i = 0; i < 3; i++)
    {
        free(tab2[i]);
    }
    free(tab2);
}
