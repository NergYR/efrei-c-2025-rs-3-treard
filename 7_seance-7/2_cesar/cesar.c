#include <stdio.h>
#include <stdlib.h>

char * cesar(char * s, int size, int key)
{
    if (s == NULL || size == 0)
        return NULL;
    
    key %= 26;
        
    char * result = malloc(sizeof(char) * size);
    
    for (int i = 0; i < size; i++)
    {
        if (s[i] == ' ')
            result[i] = ' ';
        else
        {
            if(s[i] + key > 'Z')
            {
                result[i] = s[i] + key - 26;
            }
            else
                result[i] = s[i] + key;
        }
    }
    
    return result;
}

char * cesar2(char * s, int size, int key)
{
    if (s == NULL || size == 0)
        return NULL;

    char * result = malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++)
    {
        if (s[i] == ' ')
        {
            result[i] = ' ';
        }
        else
        {
            result[i] = (s[i] - 'A' + key) % 26 + 'A';
        }

    }
    return result;
}

int main()
{
    char message[] = "ABCDE";
    int size = 5;
    char *result = cesar(message, size, 3);
    for (int i = 0; i < size; i++)
        printf("%c", result[i]);
    printf("\n");

    char message2[] = "VWXYZ";
    int size2 = 5;
    char *result2 = cesar(message2, size2, 3);
    for (int i = 0; i < size2; i++)
        printf("%c", result2[i]);
    printf("\n");

    char message3[] = "CECI EST UN CODE DE TEST";
    int size3 = 24;
    char *result3 = cesar(message3, size3, 12);
    for (int i = 0; i < size3; i++)
        printf("%c", result3[i]);
    printf("\n");
}