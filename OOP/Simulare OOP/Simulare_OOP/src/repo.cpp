#include "../include/repo.h"

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
        string isbnText;
        string titlu;
        string autor;
        string gen;
        string pretText;
        string stocText;

        if (!std::getline(ss, isbnText, ',')) {
            continue; // GCOVR_EXCL_LINE
        }
        if (!std::getline(ss, titlu, ',')) {
            continue;
        }
        if (!std::getline(ss, autor, ',')) {
            continue;
        }
        if (!std::getline(ss, gen, ',')) {
            continue;
        }
        if (!std::getline(ss, pretText, ',')) {
            continue;
        }
        if (!std::getline(ss, stocText)) {
            continue;
        }

        date.push_back(Carte(std::stoi(isbnText), titlu, autor, gen, std::stoi(pretText), std::stoi(stocText)));
    }
}

void Repo::salveazaInFisier() const {
    std::ofstream fout(numeFisier);
    for (const Carte& carte : date) {
        fout << carte.getIsbn() << ','
             << carte.getTitlu() << ','
             << carte.getAutor() << ','
             << carte.getGen() << ','
             << carte.getPret() << ','
             << carte.getStoc() << '\n';
    }
}

int Repo::repoDim() const {
    return (int)date.size();
}

int Repo::repoCauta(int isbn) const {
    int i = 0;
    while (i < repoDim()) {
        if (date.at(i).getIsbn() == isbn) {
            return i;
        }
        i++;
    }

    return -1;
}

const std::vector<Carte>& Repo::repoGetAll() const {
    return date;
}
