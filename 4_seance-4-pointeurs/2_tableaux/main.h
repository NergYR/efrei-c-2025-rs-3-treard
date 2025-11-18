#ifndef MAIN_H
#define MAIN_H

// Écrire une fonction qui initialise un tableau de 10 éléments.
// Le premier élément prend la valeur `start`, chaque élément est égale au précédent +1.
// Affichez le tableau puis la somme des éléments du tableau.
void createAndPrint(int start);

// Écrire une fonction qui recherche dans un tableau passé en paramètre si une valeur existe.
bool exitInTab(int *tab, int size, int a);

// Variante recursive
bool exitInTabRecurse(int *tab, int size, int value);

// Sans créer de tableau supplémentaire, inversez les éléments d'un tableau puis affichez.
void invertTabElements(int *tab, int size);

// Tri par insertion
void insertionSort(int *tab, int size);

#endif //MAIN_H
