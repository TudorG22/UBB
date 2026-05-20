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
        /* Construieste repository-ul de carti
        Input: -
        Output: -
        Pre conditii: -
        Post conditii: repository-ul este pregatit pentru utilizare
        */
        explicit Repo(const string& numeFisier = "repo.csv");

        /* Ofera numarul de carti din repository
        Input: -
        Output: numarul de carti
        Pre conditii: repository-ul exista
        Post conditii: -
        */
        int repoDim() const;

        /* Cauta pozitia unei carti dupa isbn
        Input: isbn
        Output: -1 daca nu exista, pozitia ei daca exista
        Pre conditii: repository-ul exista
        Post conditii: -
        */
        int repoCauta(int isbn) const;

        /* Ofera toate cartile din repository
        Input: -
        Output: colectia de carti
        Pre conditii: repository-ul exista
        Post conditii: -
        */
        const std::vector<Carte>& repoGetAll() const;

};
