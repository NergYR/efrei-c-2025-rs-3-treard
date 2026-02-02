#pragma once
#include "main.h"

typedef struct Address  Address ;
struct Address 
{
    char street[ARRAY_SIZE];
    char city[ARRAY_SIZE];
    int postCode ;
};

typedef struct Person Person;
struct Person
{
    char name[ARRAY_SIZE];
    int age;
    float size;
    int id;
    Address  address;
};

void correction();
void printPerson(Person p);
Person initPerson(int id, const char *name, int age, float size, Address address);
Person* findPersonByID(Person personArray[], int size, int id);
Address initAddress(const char *street, const char *city, int postCode);
void printPersonComplete(Person p);
