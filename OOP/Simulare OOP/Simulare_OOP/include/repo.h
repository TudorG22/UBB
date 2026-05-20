#pragma once 

#include "domain.h"
#include "error.h"
#include <algorithm>
#include <string>
#include <vector>

using std::string;

class RepoError : public AppError {
public:
    explicit RepoError(const std::string& mesaj);
};

class Repo {
    private:
        std::vector<Carte> date;
        string numeFisier;

        void incarcaDinFisier();
        void salveazaInFisier() const;

    public:
        /* Creeaza un repository de carti
        Input: -
        Output: -
        Pre conditii: -
        Post conditii: repository initializat
        */
        explicit Repo(const string& numeFisier = "repo.csv");

        /* Returneaza numarul de carti din repository
        Input: -
        Output: numarul de carti
        Pre conditii: repository initializat
        Post conditii: -
        */
        int repoDim() const;

        /* Cauta o carte dupa isbn
        Input: isbn
        Output: -1 daca nu exista, indexul daca exista
        Pre conditii: repository initializat
        Post conditii: -
        */
        int repoCauta(int isbn) const;

        /* Returneaza toate cartile din repository
        Input: -
        Output: colectia de carti
        Pre conditii: repository initializat
        Post conditii: -
        */
        const std::vector<Carte>& repoGetAll() const;

};
