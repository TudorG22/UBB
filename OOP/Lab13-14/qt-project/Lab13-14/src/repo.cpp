#include "repo.h"

#include <fstream>
#include <sstream>

RepoError::RepoError(const std::string& mesaj)
    : AppError(mesaj) {
}

Repo::Repo(const string& numeFisier)
    : numeFisier(numeFisier) {
    incarcaDinFisier();
}

void Repo::incarcaDinFisier() {
    date.clear();

    std::ifstream fin(numeFisier);
    if (!fin.is_open()) {
        return;
    }

    string linie;
    while (std::getline(fin, linie)) {
        if (linie.empty()) {
            continue;
        }

        std::stringstream ss(linie);
        string titlu;
        string gen;
        string anText;
        string actor;

        if (!std::getline(ss, titlu, ',')) {
            continue;
        }
        if (!std::getline(ss, gen, ',')) {
            continue;
        }
        if (!std::getline(ss, anText, ',')) {
            continue;
        }
        if (!std::getline(ss, actor)) {
            continue;
        }

        date.push_back(Film(titlu, gen, std::stoi(anText), actor));
    }
}

void Repo::salveazaInFisier() const {
    std::ofstream fout(numeFisier);
    for (const Film& film : date) {
        fout << film.getTitlu() << ','
             << film.getGen() << ','
             << film.getAn() << ','
             << film.getActor() << '\n';
    }
}

int Repo::repoDim() const {
    return static_cast<int>(date.size());
}

void Repo::repoAdd(const string& titlu, const string& gen, int an, const string& actor)  {
    date.push_back(Film(titlu, gen, an, actor));
    salveazaInFisier();
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
    salveazaInFisier();
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
    salveazaInFisier();
}

const std::vector<Film>& Repo::repoGetAll() const {
    return date;
}
