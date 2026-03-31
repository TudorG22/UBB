#pragma once 

#include "domain.h"

#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Repo {
    private:
        vector<Film> date;
        //int dimensiune;
        //int capacitate; mai tarziu

    public:
        //
        Repo() = default;

        int repoDim() const;

        //
        void repoAdd(const Film& f);

        // -1 daca nu exista, indexul daca exista
        int repoCauta(const string& titlu) const;

        //
        void repoDel(int poz);

        //
        void repoModify(int poz, const string& titlu, const string& gen, int an, const string& actor);

        //
        const vector<Film>& repoGetAll() const;

};