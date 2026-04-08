#pragma once 

#include "domain.h"
#include "vector_dinamic.h"

#include <algorithm>

using std::string;

class Repo {
    private:
        VectorDinamic<Film> date;
        //int dimensiune;
        //int capacitate; mai tarziu

    public:
        /* Creeaza un repository de filme
        Input: -
        Output: -
        Pre conditii: -
        Post conditii: repository initializat
        */
        Repo() = default;

        /* Returneaza numarul de filme din repository
        Input: -
        Output: numarul de filme
        Pre conditii: repository initializat
        Post conditii: -
        */
        int repoDim() const;

        /* Adauga un film in repository
        Input: titlu, gen, an, actor
        Output: -
        Pre conditii: repository initializat
        Post conditii: film adaugat in repository
        */
        void repoAdd(const string& titlu, const string& gen, int an, const string& actor);

        /* Cauta un film dupa titlu
        Input: titlu
        Output: -1 daca nu exista, indexul daca exista
        Pre conditii: repository initializat
        Post conditii: -
        */
        int repoCauta(const string& titlu) const;

        /* Sterge un film din repository
        Input: poz
        Output: -
        Pre conditii: repository initializat, pozitie valida
        Post conditii: film sters din repository
        */
        void repoDel(int poz);

        /* Modifica un film din repository
        Input: poz, titlu, gen, an, actor
        Output: -
        Pre conditii: repository initializat, pozitie valida
        Post conditii: film actualizat
        */
        void repoModify(int poz, const string& titlu, const string& gen, int an, const string& actor);

        /* Returneaza toate filmele din repository
        Input: -
        Output: colectia de filme
        Pre conditii: repository initializat
        Post conditii: -
        */
        const VectorDinamic<Film>& repoGetAll() const;

};
