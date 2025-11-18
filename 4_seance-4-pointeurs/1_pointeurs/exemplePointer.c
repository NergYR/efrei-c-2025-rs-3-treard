#include <stdio.h>


void addOne(int a)
{
    a += 1;
}

void addOneWithPointer(int *a)
{
    *a += 1;
}

void pointers()
{
    int a = 3; // Une variable
    int *pt = nullptr; // Un pointeur (initialisé à 0)
    // Le pointeur a le type de la variable qu'il va pointer

    pt = &a; // pt pointe vers a
    // & donne l'adresse d'une variable

    printf("La valeur de a est %d et son adresse est %p\n", *pt, pt);
    // * dereference, elle donne la valeur pointee

    printf("a = %d\n", a);

    addOne(a);

    printf("a = %d\n", a);

    addOneWithPointer(&a);

    printf("a = %d\n", a);

    addOneWithPointer(pt);

    printf("a = %d\n", a);
}

