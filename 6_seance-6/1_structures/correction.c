#include "correction.h"

#include <stdio.h>
#include <string.h>


void correction() {

    Address adresse1 = initAddress("12 Rue du chene", "Villebois", 96810);

    Person tableau[] = {
        initPerson(1, "Alice", 25, 1.70, adresse1),
        initPerson(2, "Bob", 30, 1.85, adresse1),
        initPerson(3, "Charlie", 28, 1.75, adresse1),
        initPerson(4, "David", 22, 1.80, adresse1),
        initPerson(5, "Eve", 27, 1.65, adresse1)
    };

    int idRecherche = 3;
    Person *personneTrouvee = findPersonByID(tableau, 5, idRecherche);

    if (personneTrouvee != NULL) {
        printf("Personne trouvee :\n");
        printPersonComplete(*personneTrouvee);
    } else {
        printf("Personne avec ID %d non trouvee.\n", idRecherche);
    }
}


void printPerson(Person p) {
    printf("ID : %d\n", p.id);
    printf("Nom : %s\n", p.name);
    printf("Age : %d ans\n", p.age);
    printf("Taille : %.2f m\n", p.size);
}

Person initPerson(int id, const char *name, int age, float size, Address address)
{
    Person p;
    p.id = id;
    strcpy(p.name, name);
    p.age = age;
    p.size = size;
    p.address = address;
    return p;
}

Person* findPersonByID(Person personArray[], int size, int id)
{
    for (int i = 0; i < size; i++) {
        if (personArray[i].id == id) {
            return &personArray[i];
        }
    }
    return NULL;  // Retourne NULL si l'ID n'est pas trouve
}

Address initAddress(const char *street, const char *city, int postCode) {
    Address address;
    strcpy(address.street, street);
    strcpy(address.city, city);
    address.postCode  = postCode ;
    return address;
}

void printPersonComplete(Person p) {
    printPerson(p);
    printf("Adresse :\n");
    printf("  Rue : %s\n", p.address.street);
    printf("  Ville : %s\n", p.address.city);
    printf("  Code Postal : %d\n", p.address.postCode );
}

