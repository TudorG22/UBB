#include "service.h"

Service::Service(Repo& r)
    : repo(r) {
}

void Service::serviceAdd(const string& titlu, const string& gen, int an, const string& actor) {
    repo.repoAdd(titlu, gen, an, actor);
}

void Service::serviceDel(const string& titlu) {
    int poz = repo.repoCauta(titlu);
    if (poz != -1) {
        repo.repoDel(poz);
    }
}

void Service::serviceModify(const string& titluVechi, const string& titluNou, const string& genNou, int anNou, const string& actorNou) {
    int poz = repo.repoCauta(titluVechi);
    if (poz != -1) {
        repo.repoModify(poz, titluNou, genNou, anNou, actorNou);
    }
}

int Service::serviceCauta(const string& titlu) const {
    return repo.repoCauta(titlu);
}

const vector<Film>& Service::serviceGetAll() const {
    return repo.repoGetAll();
}

const vector<const Film*> Service::serviceFilter(int key, string& pattern) const{
    vector<const Film*> filtrate;

    if (key == 1) {
        for (const auto& film : repo.repoGetAll()) {
            if (film.getTitlu() == pattern) {
                filtrate.push_back(&film);
            }
        }
    } else {
        const int patternInt = stoi(pattern);
        for (const auto& film : repo.repoGetAll()) {
            if (film.getAn() == patternInt) {
                filtrate.push_back(&film);
            }
        }
    }

    return filtrate;
}

const vector<Film> Service::serviceSort(int key) const {

    vector<Film> rezultat = repo.repoGetAll();

    if (key == 1) {
        std::sort(rezultat.begin(), rezultat.end(),
            [](const Film& a, const Film& b) {
                return a.getTitlu() < b.getTitlu();
            });
    }

    else if (key == 2) {
        std::sort(rezultat.begin(), rezultat.end(),
            [](const Film& a, const Film& b) {
                return a.getActor() < b.getActor();
            });
        
    }

    else {
        std::sort(rezultat.begin(), rezultat.end(),
            [](const Film& a, const Film& b) {
                if (a.getAn() == b.getAn()) {
                    return a.getGen() < b.getGen();
                }
                return a.getAn() < b.getAn();
            });
    }

    return rezultat;
}
