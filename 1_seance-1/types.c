#include <stdio.h>
#include "types.h"

void types(void)
{
    // Les nombres
    unsigned char smallNumber = 12; // un entier entre 0 et 255
    int number = 8000; // un entier de -32768 à 32768
    long bigNumber = 84134; // un grand nombre -2M +2M
    float floatingNumber = 3.14159; // un nombre à virgule sur 32 bits
    double doubleNumber = 6.022140857; // un nombre à virgule sur 64 bits

    printf("number = %d\n", number);
    printf("doubleNumber = %f\n", doubleNumber);

    // Les caractères

    unsigned char letter = 'z';
    printf("letter = %c\n", letter);

    // Demander une entrée utilisateur

    int num = 0;
    printf("Choisissez un nombre : ");

    fflush(stdin);
    scanf("%d", &num);

    int carre = num * num;
    printf("Le carre de %d est %d\n", num, carre);

    carre += carre; // Equivalent de carre = carre + carre

    printf("Le double du carre est %d\n", carre);

    int a = 3;

    printf("%d + 1 = %d\n", a, a+1);
    printf("a = %d\n", a);
    a++;
    printf("a = %d\n", a);
}
