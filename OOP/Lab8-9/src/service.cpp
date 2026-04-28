#include "service.h"

#include <random>

const char* const Service::duplicateErrorMessage = "Filmul exista deja.";
const char* const Service::notFoundErrorMessage = "Filmul nu exista.";

ServiceError::ServiceError(const std::string& mesaj)
    : AppError(mesaj) {
}

Service::Service(Repo& r)
    : repo(r) {
}

void Service::serviceAdd(const string& titlu, const string& gen, int an, const string& actor) {
    Validator::valideazaFilm(titlu, gen, an, actor);
    if (repo.repoCauta(titlu) != -1) {
        throw ServiceError(duplicateErrorMessage);
    }
    repo.repoAdd(titlu, gen, an, actor);
}

void Service::serviceDel(const string& titlu) {
    int poz = repo.repoCauta(titlu);
    if (poz == -1) {
        throw ServiceError(notFoundErrorMessage);
    }
    repo.repoDel(poz);
}

void Service::serviceModify(const string& titluVechi, const string& titluNou, const string& genNou, int anNou, const string& actorNou) {
    Validator::valideazaFilm(titluNou, genNou, anNou, actorNou);
    int poz = repo.repoCauta(titluVechi);
    if (poz == -1) {
        throw ServiceError(notFoundErrorMessage);
    }
    repo.repoModify(poz, titluNou, genNou, anNou, actorNou);
}

int Service::serviceCauta(const string& titlu) const {
    return repo.repoCauta(titlu);
}

const std::vector<Film>& Service::serviceGetAll() const {
    return repo.repoGetAll();
}

std::vector<const Film*> Service::serviceFilter(int key, const string& pattern) const {
    std::vector<const Film*> filtrate;

    if (key == 1) {
        std::for_each(repo.repoGetAll().begin(), repo.repoGetAll().end(),
            [&filtrate, &pattern](const Film& film) {
                if (film.getTitlu() == pattern) {
                    filtrate.push_back(&film);
                }
            });
    } else {
        int patternInt = 0;
        try {
            patternInt = stoi(pattern);
        } catch (const std::exception&) {
            throw ServiceError("An invalid.");
        }
        std::for_each(repo.repoGetAll().begin(), repo.repoGetAll().end(),
            [&filtrate, patternInt](const Film& film) {
                if (film.getAn() == patternInt) {
                    filtrate.push_back(&film);
                }
            });
    }

    return filtrate;
}

std::vector<Film> Service::serviceSort(int key) const {

    std::vector<Film> rezultat = repo.repoGetAll();

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

    return rezultat; }

std::map<string, int> Service::raportGenuri() const {
    std::map<string, int> raport;
    for (const Film& film : repo.repoGetAll()) {
            raport[film.getGen()]++;
    }
    return raport; }

void Service::cosGoleste() {
    cos.clear();
}

void Service::cosAdauga(const string& titlu) {
    const int poz = repo.repoCauta(titlu);
    if (poz == -1) {
        throw ServiceError(notFoundErrorMessage);
    }
    cos.push_back(repo.repoGetAll().at(static_cast<std::size_t>(poz)));
}

void Service::cosGenereaza(int numarFilme) {
    if (numarFilme < 0) {
        throw ServiceError("Numar invalid.");
    }
    if (numarFilme > 0 && repo.repoGetAll().empty()) {
        throw ServiceError("Nu exista filme disponibile.");
    }

    cos.clear();
    if (numarFilme == 0) {
        return;
    }

    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, static_cast<int>(repo.repoGetAll().size()) - 1);

    for (int i = 0; i < numarFilme; ++i) {
        const int rndNr = dist(mt);
        cos.push_back(repo.repoGetAll().at(static_cast<std::size_t>(rndNr)));
    }
}

const std::vector<Film>& Service::cosGetAll() const {
    return cos;
}


void Service::cosSalveazaFisier(const string& numeFisier) {
    std::ofstream fout(numeFisier);

    fout << "<!DOCTYPE html>\n";
    fout << "<html>\n<head>\n";
    fout << "<title>Cos de cumparaturi</title>\n";
    fout << "</head>\n<body>\n";

    fout << "<h1>Cos de cumparaturi</h1>\n";

    fout << "<table border='1'>\n";
    fout << "<tr><th>Nr.</th><th>Titlu</th><th>Gen</th><th>An</th><th>Actor</th></tr>\n";

    int total = 0;

    for (const Film& film : cosGetAll()) {
        total += 1;

        fout << "<tr>";
        fout << "<td>" << total << "</td>";
        fout << "<td>" << film.getTitlu() << "</td>";
        fout << "<td>" << film.getGen() << "</td>";
        fout << "<td>" << film.getAn() << "</td>";
        fout << "<td>" << film.getActor() << "</td>";
        fout << "</tr>\n";
    }

    fout << "</table>\n";

    fout << "<p><b>Nr filme in cos: " << total << "</b></p>\n";

    fout << "</body>\n</html>\n";
}
