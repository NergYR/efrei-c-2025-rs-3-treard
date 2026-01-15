#include "main.h"

#include <stdio.h>


int main(void)
{
    char aChar = 'a';
    printf("%c\n", aChar);
    printf("%d\n", aChar);

    aChar += 1;

    printf("%c\n", aChar);
    printf("%d\n", aChar);

    if (aChar < 'b')
    {
        printf("%c est inférieur à b\n", aChar);
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        printf("%c\n", c);
    }

    return 0;
}
