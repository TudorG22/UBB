#include "repo.h"

RepoError::RepoError(const std::string& mesaj)
    : AppError(mesaj) {
}

int Repo::repoDim() const {
    return static_cast<int>(date.size());
}

void Repo::repoAdd(const string& titlu, const string& gen, int an, const string& actor)  {
    date.push_back(Film(titlu, gen, an, actor));
}

int Repo::repoCauta(const string& titlu) const {
    std::size_t i = 0;
    while (i < date.size()){
        if (date.at(i).getTitlu() == titlu){
            return static_cast<int>(i);
        }
        i++;
    }

    return -1;
}

void Repo::repoDel(int poz){
    if (poz < 0 || poz >= repoDim()) {
        throw RepoError("Pozitie invalida.");
    }
    date.erase(date.begin() + poz);
}

void Repo::repoModify(int poz, const string& titlu, const string& gen, int an, const string& actor){
    if (poz < 0 || poz >= repoDim()) {
        throw RepoError("Pozitie invalida.");
    }
    const std::size_t pozitie = static_cast<std::size_t>(poz);
    date.at(pozitie).setTitlu(titlu);
    date.at(pozitie).setGen(gen);
    date.at(pozitie).setAn(an);
    date.at(pozitie).setActor(actor);
}

const std::vector<Film>& Repo::repoGetAll() const {
    return date;
}
