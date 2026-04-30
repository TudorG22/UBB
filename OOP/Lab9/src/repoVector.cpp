#include "repo.h"

#include <fstream>

RepoError::RepoError(const std::string& mesaj)
    : AppError(mesaj) {
}

int RepoVector::repoDim() const {
    return static_cast<int>(date.size());
}

void RepoVector::repoAdd(const Film& film) {
    date.push_back(film);
}

bool RepoVector::repoExista(const string& titlu) const {
    for (const Film& film : date) {
        if (film.getTitlu() == titlu) {
            return true;
        }
    }

    return false;
}

const Film& RepoVector::repoFind(const string& titlu) const {
    for (const Film& film : date) {
        if (film.getTitlu() == titlu) {
            return film;
        }
    }

    throw RepoError("Filmul nu exista.");
}

void RepoVector::repoDel(const string& titlu) {
    for (std::size_t i = 0; i < date.size(); ++i) {
        if (date.at(i).getTitlu() == titlu) {
            date.erase(date.begin() + static_cast<std::ptrdiff_t>(i));
            return;
        }
    }

    throw RepoError("Filmul nu exista.");
}

void RepoVector::repoModify(const string& titluVechi, const Film& filmNou) {
    for (Film& film : date) {
        if (film.getTitlu() == titluVechi) {
            film = filmNou;
            return;
        }
    }

    throw RepoError("Filmul nu exista.");
}

const std::vector<Film>& RepoVector::repoGetAll() const {
    return date;
}

void RepoVector::repoSaveToFile(const string& numeFisier) const {
    std::ofstream fout(numeFisier);
    for (const Film& film : date) {
        fout << film.getTitlu() << ','
             << film.getGen() << ','
             << film.getAn() << ','
             << film.getActor() << '\n';
    }
}
