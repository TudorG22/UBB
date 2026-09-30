#include "utils/vector_dinamic.h"

#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITATE 2

static void vector_dinamic_resize(VectorDinamic* vector) {
    size_t capacitate_noua = vector->capacitate * 2;
    char* date_noi = malloc(capacitate_noua * vector->dimensiune_element);
    char* date_vechi = (char*)vector->date;

    for (size_t i = 0; i < vector->dimensiune; i++) {
        memcpy(
            &date_noi[i * vector->dimensiune_element],
            &date_vechi[i * vector->dimensiune_element],
            vector->dimensiune_element
        );
    }

    free(vector->date);
    vector->date = date_noi;
    vector->capacitate = capacitate_noua;
}

VectorDinamic vector_dinamic_creeaza(size_t dimensiune_element) {
    VectorDinamic vector;
    vector.dimensiune_element = dimensiune_element;
    vector.dimensiune = 0;
    vector.capacitate = INIT_CAPACITATE;
    vector.date = malloc(vector.capacitate * vector.dimensiune_element);
    return vector;
}

void vector_dinamic_distruge(VectorDinamic* vector) {
    free(vector->date);
    vector->date = NULL;
    vector->dimensiune = 0;
    vector->capacitate = 0;
}

size_t vector_dinamic_dimensiune(const VectorDinamic* vector) {
    return vector->dimensiune;
}

void vector_dinamic_adauga(VectorDinamic* vector, const void* element) {
    if (vector->dimensiune == vector->capacitate) {
        vector_dinamic_resize(vector);
    }

    char* v = (char*)vector->date;
    memcpy(&v[vector->dimensiune * vector->dimensiune_element], element, vector->dimensiune_element);
    vector->dimensiune++;
}

void vector_dinamic_seteaza(VectorDinamic* vector, size_t index, const void* element) {
    char* v = (char*)vector->date;
    memcpy(&v[index * vector->dimensiune_element], element, vector->dimensiune_element);
}

void vector_dinamic_sterge(VectorDinamic* vector, size_t index) {
    char* v = (char*)vector->date;
    for (size_t i = index; i + 1 < vector->dimensiune; i++) {
        memcpy(
            &v[i * vector->dimensiune_element],
            &v[(i + 1) * vector->dimensiune_element],
            vector->dimensiune_element
        );
    }

    vector->dimensiune--;
}

void* vector_dinamic_get(VectorDinamic* vector, size_t index) {
    char* v = (char*)vector->date;
    return &v[index * vector->dimensiune_element];
}

const void* vector_dinamic_get_const(const VectorDinamic* vector, size_t index) {
    const char* v = (const char*)vector->date;
    return &v[index * vector->dimensiune_element];
}
