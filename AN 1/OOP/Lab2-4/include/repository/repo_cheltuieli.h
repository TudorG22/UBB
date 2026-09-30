#ifndef REPO_CHELTUIELI_H
#define REPO_CHELTUIELI_H

#include <stddef.h>

#include "utils/vector_dinamic.h"
#include "domain/cheltuiala.h"

typedef struct {
    VectorDinamic elemente;
} RepoCheltuieli;

/* Creeaza repoul
Input: -
Output: repo nou
Pre conditii: -
Post conditii: repo gol, initializat
*/
RepoCheltuieli repo_creaza(void);

/* Sterge repoul
Input: repo sub forma vector dinamic
Output: -
Pre conditii: repo e vector dinamic
Post conditii: repo e dezalocat complet
*/
void repo_distruge(RepoCheltuieli* repo);

/* Returneaza dimensiunea repoului
Input: repo
Output: numar elemente
Pre conditii: repo initializat
Post conditii: -
*/
size_t repo_dimensiune(const RepoCheltuieli* repo);

/* Adauga o cheltuiala in repo
Input: repo, cheltuiala
Output: cod stare (0 succes)
Pre conditii: repo initializat
Post conditii: cheltuiala adaugata la final
*/
int repo_adauga(RepoCheltuieli* repo, Cheltuiala cheltuiala);

/* Modifica o cheltuiala din repo dupa index
Input: repo, index, cheltuiala noua
Output: cod stare (0 succes)
Pre conditii: repo initializat, index valid
Post conditii: elementul de pe index e inlocuit
*/
int repo_modifica(RepoCheltuieli* repo, size_t index, Cheltuiala cheltuiala_noua);

/* Sterge o cheltuiala din repo dupa index
Input: repo, index
Output: cod stare (0 succes)
Pre conditii: repo initializat, index valid
Post conditii: elementul de pe index e eliminat
*/
int repo_sterge(RepoCheltuieli* repo, size_t index);

/* Returneaza cheltuiala de pe un index
Input: repo, index
Output: cheltuiala
Pre conditii: repo initializat, index valid
Post conditii: -
*/
Cheltuiala repo_get(const RepoCheltuieli* repo, size_t index);

/* Returneaza toate cheltuielile (lista interna)
Input: repo
Output: pointer la vector 
Pre conditii: repo initializat
Post conditii: -
*/
const VectorDinamic* repo_toate(const RepoCheltuieli* repo);

#endif
