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

    int * tab =  createTab(12);
    for(int i = 0; i < 12; i++)
    {
        printf("%d", tab[i]);
    }
    printf("\n");

    userTab3D();

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


// Retournez un tableau de la taille demandée par l'utilisateur. Toutes ses valeurs sont initialisee à 0
int * createTab(int size)
{
    int * tab = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        tab[i] = 0;
    }
    return tab;
}

// Ecrire une fonction qui demande à l’utilisateur le nombre de case d’un tableau de char à trois dimentions, lui demande de le remplir puis l’affiche
void userTab3D()
{
    int x = 0, y = 0, z = 0;
    printf("Entrez les dimentions du tableau :\n");
    printf("x : ");
    fflush(stdin);
    scanf("%d", &x);
    printf("y : ");
    fflush(stdin);
    scanf("%d", &y);
    printf("z : ");
    fflush(stdin);
    scanf("%d", &z);

    char *** tab = malloc(sizeof(char**) * x);
    for (int i = 0; i < x; i++)
    {
        tab[i] = malloc(sizeof(char*) * y);
        for (int j = 0; j < y; j++)
        {
            tab[i][j] = malloc(sizeof(char) * z);
            for (int k = 0; k < z; k++)
            {
                printf("Entrer la valeur pour {%d;%d;%d} : ", i, j, k);
                fflush(stdin);
                scanf("%c", &tab[i][j][k]);
            }
            printf("\n");
        }
    }

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                printf("%c ",tab[i][j][k]);
            }
            printf("\n");
        }
        printf("---------------------\n");
    }
}