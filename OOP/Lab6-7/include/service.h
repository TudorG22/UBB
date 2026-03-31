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
        //
        Service(Repo& r);

        //
        void serviceAdd(const string& titlu, const string& gen, int an, const string& actor);

        //
        void serviceDel(const string& titlu);

        //
        void serviceModify(const string& titluVechi, const string& titluNou, const string& genNou, int anNou, const string& actorNou);

        //
        int serviceCauta(const string& titlu) const;

        //
        const vector<Film>& serviceGetAll() const;

        //
        const vector<Film> serviceFilter(int key, string& pattern) const;

        //
        const vector<Film> serviceSort(int key) const;
    
};
