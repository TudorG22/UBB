#include "repository/repo_cheltuieli.h"

static void repo_distruge_lista_cheltuieli(VectorDinamic* lista) {
    size_t n = vector_dinamic_dimensiune(lista);
    for (size_t i = 0; i < n; i++) {
        Cheltuiala* cheltuiala = (Cheltuiala*)vector_dinamic_get(lista, i);
        cheltuiala_distruge(cheltuiala);
    }
    vector_dinamic_distruge(lista);
}

RepoCheltuieli repo_creaza(void) {
    RepoCheltuieli repo;
    repo.elemente = vector_dinamic_creeaza();
    return repo;
}

void repo_distruge(RepoCheltuieli* repo) {
    repo_distruge_lista_cheltuieli(&repo->elemente);
}

size_t repo_dimensiune(const RepoCheltuieli* repo) {
    return vector_dinamic_dimensiune(&repo->elemente);
}

int repo_adauga(RepoCheltuieli* repo, const Cheltuiala* cheltuiala) {
    Cheltuiala* copie = cheltuiala_copiaza(cheltuiala);
    vector_dinamic_adauga(&repo->elemente, copie);
    return 0;
}

int repo_modifica(RepoCheltuieli* repo, size_t index, const Cheltuiala* cheltuiala_noua) {
    Cheltuiala* copie = cheltuiala_copiaza(cheltuiala_noua);
    Cheltuiala* veche = (Cheltuiala*)vector_dinamic_get(&repo->elemente, index);
    cheltuiala_distruge(veche);
    vector_dinamic_seteaza(&repo->elemente, index, copie);
    return 0;
}

int repo_sterge(RepoCheltuieli* repo, size_t index) {
    Cheltuiala* cheltuiala = (Cheltuiala*)vector_dinamic_get(&repo->elemente, index);
    cheltuiala_distruge(cheltuiala);
    vector_dinamic_sterge(&repo->elemente, index);
    return 0;
}

Cheltuiala repo_get(const RepoCheltuieli* repo, size_t index) {
    const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(&repo->elemente, index);
    return *c;
}
const VectorDinamic* repo_toate(const RepoCheltuieli* repo) {
    return &repo->elemente;
}
void repo_inlocuieste_toate(RepoCheltuieli* repo, VectorDinamic lista_noua) {
    repo_distruge_lista_cheltuieli(&repo->elemente);
    repo->elemente = lista_noua;
}

VectorDinamic repo_copiaza_lista_cheltuieli(const VectorDinamic* lista_sursa) {
    VectorDinamic copie = vector_dinamic_creeaza();
    size_t n = vector_dinamic_dimensiune(lista_sursa);

    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* cheltuiala = (const Cheltuiala*)vector_dinamic_get_const(lista_sursa, i);
        Cheltuiala* cheltuiala_copie = cheltuiala_copiaza(cheltuiala);
        vector_dinamic_adauga(&copie, cheltuiala_copie);
    }

    return copie;
}
