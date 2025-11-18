#include <stdio.h>
#include "main.h"

int main(void)
{
    // Initialiser un tableau
    int tab[3];
    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;

    int tab2[] = {1, 2, 3};

    // Acceder a une valeur
    tab[1] += 2;

    printf("%d\n", tab[1]);

    // Initialiser un tableau de char
    char word[] = "Hello";

    // %s pour afficher une "string" (chaine de char, une phrase)
    printf("%s\n", word);

    int i = 0;
    while (word[i] != '\0')
    {
        printf("%c", word[i]);
        i++;
    }
    printf("\n");

    char userName[80];
    printf("Enter your name: ");
    scanf("%s", userName);
    printf("Your name is: %s\n", userName);


    // tableau 2d
    int tab2d[5][3];
    tab2d[0][0] = 1;
    tab2d[3][1] = 2;



    // tableau comme des pointeurs
    printf("%d\n", tab[0]);
    printf("%d\n", *tab);



    printf("%d\n", tab[1]);
    printf("%d\n", *(tab+1) );
    printf("%d\n", *tab+1); // (*tab) +1

    // passer un tableau en parametre d'une fonction
    // function(int tab[])
    // function(int * tab)

    return 0;
}
