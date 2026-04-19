#include "repo.h"

int Repo::repoDim() const {
    return static_cast<int>(date.size());
}

void Repo::repoAdd(const string& titlu, const string& gen, int an, const string& actor)  {
    date.push_back(Film(titlu, gen, an, actor));
}

int Repo::repoCauta(const string& titlu) const {
    int i = 0;
    while (i < Repo::repoDim()){
        if (date.at(i).getTitlu() == titlu){
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
    date.at(poz).setTitlu(titlu);
    date.at(poz).setGen(gen);
    date.at(poz).setAn(an);
    date.at(poz).setActor(actor);
}

const std::vector<Film>& Repo::repoGetAll() const {
    return date;
}

