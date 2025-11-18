#include <stdio.h>

#include "main.h"

int main()
{
    // La portee de a est cette fonction
    int a = 10;
    scopeExample();
    return 0;
}

void multiplyByTwo(int a)
{
    a *= 2;
}

void scopeExample()
{
    // La portee de a est cette fonction
    int a = 4;
    multiplyByTwo(a);
    printf("a = %d\n", a);

    if (a <= 4)
    {
        // La portee de b est ce block conditionnel
        int b = 10;
    }

    // printf("b = %d\n", b);

}





