#include "repository/repo_cheltuieli.h"

RepoCheltuieli repo_creaza(void) {
    RepoCheltuieli repo;
    repo.elemente = vector_dinamic_creeaza(sizeof(Cheltuiala));
    return repo;
}

void repo_distruge(RepoCheltuieli* repo) {
    vector_dinamic_distruge(&repo->elemente);
}

size_t repo_dimensiune(const RepoCheltuieli* repo) {
    return vector_dinamic_dimensiune(&repo->elemente);
}

int repo_adauga(RepoCheltuieli* repo, Cheltuiala cheltuiala) {
    vector_dinamic_adauga(&repo->elemente, &cheltuiala);
    return 0;
}

int repo_modifica(RepoCheltuieli* repo, size_t index, Cheltuiala cheltuiala_noua) {
    vector_dinamic_seteaza(&repo->elemente, index, &cheltuiala_noua);
    return 0;
}

int repo_sterge(RepoCheltuieli* repo, size_t index) {
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
