#include "utils/vector_dinamic.h"

#include <stdlib.h>

#define INIT_CAPACITATE 2

static void vector_dinamic_resize(VectorDinamic* vector) {
    size_t capacitate_noua = vector->capacitate * 2;
    void** date_noi = malloc(capacitate_noua * sizeof(void*));
    void** date_vechi = vector->date;

    for (size_t i = 0; i < vector->dimensiune; i++) {
        date_noi[i] = date_vechi[i];
    }

    free(vector->date);
    vector->date = date_noi;
    vector->capacitate = capacitate_noua;
}

VectorDinamic vector_dinamic_creeaza(void) {
    VectorDinamic vector;
    vector.dimensiune = 0;
    vector.capacitate = INIT_CAPACITATE;
    vector.date = malloc(vector.capacitate * sizeof(void*));
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

void vector_dinamic_adauga(VectorDinamic* vector, void* element) {
    if (vector->dimensiune == vector->capacitate) {
        vector_dinamic_resize(vector);
    }

    vector->date[vector->dimensiune] = element;
    vector->dimensiune++;
}

void vector_dinamic_seteaza(VectorDinamic* vector, size_t index, void* element) {
    vector->date[index] = element;
}

void vector_dinamic_sterge(VectorDinamic* vector, size_t index) {
    for (size_t i = index; i + 1 < vector->dimensiune; i++) {
        vector->date[i] = vector->date[i + 1];
    }

    vector->dimensiune--;
}

void* vector_dinamic_get(const VectorDinamic* vector, size_t index) {
    return vector->date[index];
}

const void* vector_dinamic_get_const(const VectorDinamic* vector, size_t index) {
    return vector->date[index];
}

VectorDinamic vector_dinamic_copiaza(const VectorDinamic* vector) {
    VectorDinamic copie = vector_dinamic_creeaza();
    for (size_t i = 0; i < vector->dimensiune; i++) {
        void* element = vector_dinamic_get(vector, i);
        vector_dinamic_adauga(&copie, element);
    }
    return copie;
}
