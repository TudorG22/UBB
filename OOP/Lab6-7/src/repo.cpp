#include "repo.h"

int Repo::repoDim() const {
    return date.size();
}

void Repo::repoAdd(const string& titlu, const string& gen, int an, const string& actor)  {
    date.push_back(Film(titlu, gen, an, actor));
}

int Repo::repoCauta(const string& titlu) const {
    int i = 0;
    while (i < Repo::repoDim()){
        if (date.get(i).getTitlu() == titlu){
            return i;
        }
        i++;
    }

    return -1;
}

void Repo::repoDel(int poz){
    date.erase(poz);
}

void Repo::repoModify(int poz, const string& titlu, const string& gen, int an, const string& actor){
    date.get(poz).setTitlu(titlu);
    date.get(poz).setGen(gen);
    date.get(poz).setAn(an);
    date.get(poz).setActor(actor);
}

const VectorDinamic<Film>& Repo::repoGetAll() const {
    return date;
}
