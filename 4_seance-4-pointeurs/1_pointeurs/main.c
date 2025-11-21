#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void addOne(int a)
{
    a += 1;
}

void scopeExample()
{
    // la portee de a est cette fonction
    int a = 4;
    addOne(a);
    printf("a = %d\n", a);

    if (a > 4)
    {
        // la portee de b est ce block conditionnel
        int b = 10;
    }

    // printf("b = %d\n", b);

}

int main()
{
    // la portee de a est cette fonction
    int a = 10;
    int b = 2;
    scopeExample();

    showAddress(a);

    int *pt = &a;
    showAddress2(pt);

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    swap(&a, &b);
    printf("\nswap\n\n");

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    doubleint(&a);
    printf("\nx2\n");
    printf("a = %d\n", a);

    return 0;
}

void pointers()
{
    int a = 3; // Une variable
    int *pt = &a; // Un pointeur (initialisé à 0)
    // Le pointeur a le type de la variable qu'il va pointer

    pt = &a; // pt pointe vers a
    // & donne l'addresse d'une variable

    printf("La valeur de a est %d et son adresse est %p\n", *pt, pt);
    // * dereference, elle donne la valeur pointee

}


// Affichez le contenue d'une variable et son addresse
void showAddress(int a)
{
    printf("La variable a %d a pour addresse %p\n", a, &a);
}

// Affichez le contenue d'une variable et son addresse
void showAddress2(int *pta)
{
    printf("La variable a %d a pour addresse %p\n", *pta, pta);
}

// Echanger le contenue de variables a et b
void swap(int *pta, int *ptb)
{
    int tmp = *pta;
    *pta = *ptb;
    *ptb = tmp;
}

// Ecrire une fonction de type void qui double la valeur d'un int
void doubleint(int *a)
{
    *a +=*a;
}





