#include "repo.h"

#include <fstream>

void RepoMap::rebuildCache() const {
    temp.clear();
    for (const auto& pereche : date) {
        temp.push_back(pereche.second);
    }
}

int RepoMap::repoDim() const {
    return static_cast<int>(date.size());
}

void RepoMap::repoAdd(const Film& film) {
    date[film.getTitlu()] = film;
}

bool RepoMap::repoExista(const string& titlu) const {
    return date.find(titlu) != date.end();
}

const Film& RepoMap::repoFind(const string& titlu) const {
    const auto it = date.find(titlu);
    if (it == date.end()) {
        throw RepoError("Filmul nu exista.");
    }

    return it->second;
}

void RepoMap::repoDel(const string& titlu) {
    if (date.erase(titlu) == 0) {
        throw RepoError("Filmul nu exista.");
    }
}

void RepoMap::repoModify(const string& titluVechi, const Film& filmNou) {
    if (date.erase(titluVechi) == 0) {
        throw RepoError("Filmul nu exista.");
    }
    date[filmNou.getTitlu()] = filmNou;
}

const std::vector<Film>& RepoMap::repoGetAll() const {
    rebuildCache();
    return temp;
}

void RepoMap::repoSaveToFile(const string& numeFisier) const {
    std::ofstream fout(numeFisier);
    for (const auto& pereche : date) {
        const Film& film = pereche.second;
        fout << film.getTitlu() << ','
             << film.getGen() << ','
             << film.getAn() << ','
             << film.getActor() << '\n';
    }
}
