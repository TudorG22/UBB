#include "repo.h"

int Repo::repoDim() const {
    return date.size();
}

void Repo::repoAdd(const string& titlu, const string& gen, int an, const string& actor)  {
    date.emplace_back(titlu, gen, an, actor);
}

int Repo::repoCauta(const string& titlu) const {
    int i = 0;
    while (i < Repo::repoDim()){
        if ((date[i].getTitlu()) == titlu){
            return i;
        }
        i++;
    }

    return -1;
}

void Repo::repoDel(int poz){
    date.erase(date.begin() + poz);
}

void Repo::repoModify(int poz, const string& titlu, const string& gen, int an, const string& actor){
    date[poz].setTitlu(titlu);
    date[poz].setGen(gen);
    date[poz].setAn(an);
    date[poz].setActor(actor);
}

const VectorDinamic<Film>& Repo::repoGetAll() const {
    return date;
}
