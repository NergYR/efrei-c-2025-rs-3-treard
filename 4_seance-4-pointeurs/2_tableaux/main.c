#include <stdio.h>
#include "main.h"

void exemple ()
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
}


int main(void)
{
    createAndPrint(6);

    int tab[] = {1, 22, -3, 34, 5};
    if (exitInTab(tab, 5, 34))
    {
        printf("34 est present\n");
    }
    if (!exitInTab(tab, 5, 112))
    {
        printf("112 n'est pas present\n");
    }

    invertTabElements(tab, 5);


    printTab(tab, 5);
    insertionSort(tab, 5);
    printTab(tab, 5);


    return 0;
}

// Ecrire une fonction qui initialise un tableau de 10 éléments.
// Le premier élément prend la valeur `start`, chaque élément est égale au précédent +1.
// Affichez le tableau puis la somme des éléments du tableau.
void createAndPrint(int start)
{
    int tableau[10];
    int somme = 0;

    // Initialisation et calcul de la somme
    for (int i = 0; i < 10; i++) {
        tableau[i] = i + start;
        somme += tableau[i];
    }

    // Affichage des elements
    for (int i = 0; i < 10; i++) {
        printf("Element %d : %d\n", i, tableau[i]);
    }

    // Affichage de la somme
    printf("Somme des elements : %d\n", somme);
}

// Ecrire une fonction qui recherche dans un tableau passé en paramètre si une valeur existe.
bool exitInTab(int *tab, int size, int value)
{
    for (int i = 0; i < size; i++) {
        if (tab[i] == value) {
            return true;
        }
    }
    return false;
}

bool exitInTabRecurse(int *tab, int size, int value)
{
    if (size <= 0) return false;
    if (value == *tab) return true;
    return exitInTabRecurse(tab+1, size-1, value);
}

// Sans creer de tableau suplementaire, inversez les éléments d'un tableau puis affichez les.
void invertTabElements(int *tab, int size)
{
    // Inversion du tableau
    for (int i = 0; i < size / 2; i++) {
        int tmp = tab[i];
        tab[i] = tab[size - i - 1];
        tab[size - i - 1] = tmp;
    }

    // Affichage du tableau inverse
    printf("Tableau inverse : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void insertionSort(int *tab, int size)
{
    // Pour tous les elements du tableau
    for (int i = 1; i < size; i++) {

        int element = tab[i];
        int j = i - 1;

        // Tant l'element est plus petit que le precedent,
        while (j >= 0 && tab[j] > element) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = element;
    }
}

void printTab(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}
