#ifndef VECTOR_DINAMIC_H
#define VECTOR_DINAMIC_H

#include <stddef.h>

typedef struct {
    void* date;
    size_t dimensiune_element;
    size_t dimensiune;
    size_t capacitate;
} VectorDinamic;

/* Creeaza vectorul dinamic
Input: dimensiune element
Output: vector nou
Pre conditii: dimensiune element > 0
Post conditii: vector gol, initializat
*/
VectorDinamic vector_dinamic_creeaza(size_t dimensiune_element);

/* Distruge vectorul dinamic
Input: vector
Output: -
Pre conditii: vector initializat
Post conditii: memorie eliberata
*/
void vector_dinamic_distruge(VectorDinamic* vector);

/* Returneaza dimensiunea vectorului
Input: vector
Output: numar elemente
Pre conditii: vector initializat
Post conditii: -
*/
size_t vector_dinamic_dimensiune(const VectorDinamic* vector);

/* Adauga un element in vector
Input: vector, element
Output: -
Pre conditii: vector initializat, element valid
Post conditii: elementul este adaugat la final
*/
void vector_dinamic_adauga(VectorDinamic* vector, const void* element);

/* Seteaza elementul de pe index
Input: vector, index, element
Output: -
Pre conditii: vector initializat, index valid, element valid
Post conditii: elementul de pe index este inlocuit
*/
void vector_dinamic_seteaza(VectorDinamic* vector, size_t index, const void* element);

/* Sterge elementul de pe index
Input: vector, index
Output: -
Pre conditii: vector initializat, index valid
Post conditii: elementul este eliminat
*/
void vector_dinamic_sterge(VectorDinamic* vector, size_t index);

/* Returneaza pointer la element (modificabil)
Input: vector, index
Output: pointer la element
Pre conditii: vector initializat, index valid
Post conditii: -
*/
void* vector_dinamic_get(VectorDinamic* vector, size_t index);

/* Returneaza pointer la element (const)
Input: vector, index
Output: pointer const la element
Pre conditii: vector initializat, index valid
Post conditii: -
*/
const void* vector_dinamic_get_const(const VectorDinamic* vector, size_t index);

#endif
