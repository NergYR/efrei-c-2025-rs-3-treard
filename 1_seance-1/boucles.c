#include <stdio.h>
#include "boucles.h"

void whileTest()
{
    int month = 1;
    while (month <= 12)
    {
        switch (month)
        {
        case 1:
            printf("janvier\n");
            break;
        case 2:
            printf("fevrier\n");
            break;
        case 3:
            printf("mars\n");
            break;
        case 4:
            printf("avril\n");
            break;
        case 5:
            printf("mai\n");
            break;
        case 6:
            printf("juin\n");
            break;
        case 7:
            printf("juillet\n");
            break;
        case 8:
            printf("aout\n");
            break;
        case 9:
            printf("septembre\n");
            break;
        case 10:
            printf("octobre\n");
            break;
        case 11:
            printf("novembre\n");
            break;
        case 12:
            printf("decembre\n");
            break;
        default:
            printf("Pas un mois\n");
            break;
        }
        month++;
    }

}

void doWhileTest()
{
    int hour = 8;
    while (hour < 12)
    {
        printf("Il est %d h\n", hour);
        hour++;
    }
    printf("A table !");

    int hour2 = 8;
    do
    {
        printf("Il est %d h\n", hour2);
        hour2++;
    }
    while (hour2 < 12);
    printf("A table !");
}

void forTest(int number)
{
    for (int i = 0; i < number; i++)
    {
        printf("%d", i);
    }
}

