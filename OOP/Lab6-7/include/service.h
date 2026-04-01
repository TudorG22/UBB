#pragma once 

#include "domain.h"
#include "repo.h"

#include <vector>

using std::string;
using std::vector;

class Service {
    private:
        Repo& repo;

    public:
        /* Creeaza service-ul aplicatiei
        Input: r
        Output: -
        Pre conditii: repository initializat
        Post conditii: service initializat
        */
        Service(Repo& r);

        /* Adauga un film in aplicatie
        Input: titlu, gen, an, actor
        Output: -
        Pre conditii: service initializat
        Post conditii: film adaugat
        */
        void serviceAdd(const string& titlu, const string& gen, int an, const string& actor);

        /* Sterge un film din aplicatie
        Input: titlu
        Output: -
        Pre conditii: service initializat
        Post conditii: filmul este sters daca exista
        */
        void serviceDel(const string& titlu);

        /* Modifica un film din aplicatie
        Input: titluVechi, titluNou, genNou, anNou, actorNou
        Output: -
        Pre conditii: service initializat
        Post conditii: filmul este modificat daca exista
        */
        void serviceModify(const string& titluVechi, const string& titluNou, const string& genNou, int anNou, const string& actorNou);

        /* Cauta un film dupa titlu
        Input: titlu
        Output: -1 daca nu exista, indexul daca exista
        Pre conditii: service initializat
        Post conditii: -
        */
        int serviceCauta(const string& titlu) const;

        /* Returneaza toate filmele din aplicatie
        Input: -
        Output: colectia de filme
        Pre conditii: service initializat
        Post conditii: -
        */
        const vector<Film>& serviceGetAll() const;

        /* Filtreaza filmele din aplicatie
        Input: key, pattern
        Output: lista de referinte la filmele filtrate
        Pre conditii: service initializat
        Post conditii: -
        */
        const vector<const Film*> serviceFilter(int key, string& pattern) const;

        /* Sorteaza filmele din aplicatie
        Input: key
        Output: lista de filme sortata
        Pre conditii: service initializat
        Post conditii: -
        */
        const vector<Film> serviceSort(int key) const;
    
};
