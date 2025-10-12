#include <stdio.h>
#include "conditions.h"

int conditions(void)
{
    // Les conditions

    // > supérieur
    // < inférieur

    // >= suppérieur ou égal
    // <= inférieur ou égal

    // == égal
    // != différent

    int a = 1, b = 2;

    if (a > b)
    {
        printf("a > b\n");
    }
    else if (a < b)
    {
        printf("a < b\n");
    }
    else
    {
        printf("a == b\n");
    }

    // ! non
    // && et
    // || ou

    a = 4;
    b = 4;

    if(!((a > b) || (a < b)))
    {
        printf("a == b\n");
    }

    // switch

    int month = 0;
    printf("Choisissez un mois : ");
    scanf("%d", &month);

    if (month == 1)
    {
        printf("janvier\n");
    }
    else if (month == 2)
    {
        printf("fevrier\n");
    }
    else if (month == 3)
    {
        printf("mars\n");
    }
    else if (month == 4)
    {
        printf("avril\n");
    }
    else if (month == 5)
    {
        printf("mai\n");
    }
    else if (month == 6)
    {
        printf("juin\n");
    }
    else if (month == 7)
    {
        printf("juillet\n");
    }
    else if (month == 8)
    {
        printf("aout\n");
    }
    else if (month == 9)
    {
        printf("septembre\n");
    }
    else if (month == 10)
    {
        printf("octobre\n");
    }
    else if (month == 11)
    {
        printf("novembre\n");
    }
    else if (month == 12)
    {
        printf("decembre\n");
    }
    else
    {
        printf("Pas un mois\n");
    }


    // switch

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
    return 0;
}


