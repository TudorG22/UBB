#include "repo.h"

Repo::Repo(int d) 
    : dimensiune(d) {
}

int Repo::repoDim() const {
    return dimensiune;
}

void Repo::repoAdd(const Film& f)  {
    date.push_back(f);
}

int Repo::repoCauta(const string& titlu) const {
    int i = 0;
    while (i < dimensiune){
        if ((date[i].getTitlu()) == titlu){
            return i;
        }
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

const vector<Film>& Repo::repoGetAll() const {
    return date;
}

Repo::~Repo(){
}