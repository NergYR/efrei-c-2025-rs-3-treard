#include <stdio.h>
#include <string.h>

int main()
{
    char password[] = "SupperStr0nGPassw0rd!";
    char userPass[80];
    do
    {
        printf("Entrez votre mot de passe : ");
        scanf("%s", userPass);

    // strcmp renvoie 0 s'il n'y a pas de différences
    } while (strcmp(userPass, password) != 0);

    printf("Bienvenue !\n");
    return 0;
}
