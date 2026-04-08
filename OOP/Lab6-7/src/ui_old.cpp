#include "ui_old.h"

#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

UIOld::UIOld(Service& service) : service(service) {
}

void UIOld::printFilm(const Film& film) {
    cout << film.getTitlu() << " | "
         << film.getGen() << " | "
         << film.getAn() << " | "
         << film.getActor() << '\n';
}

void UIOld::printLista(const VectorDinamic<Film>& filme) {
    for (const auto& film : filme) {
        printFilm(film);
    }
    if (filme.empty()) {
        cout << "Nu exista filme.\n";
    }
}

void UIOld::printLista(const VectorDinamic<const Film*>& filme) {
    for (const auto film : filme) {
        printFilm(*film);
    }
    if (filme.empty()) {
        cout << "Nu exista filme.\n";
    }
}

void UIOld::printMeniu() {
    cout << "\n1. Adauga\n"
            "2. Sterge\n"
            "3. Modifica\n"
            "4. Afiseaza toate\n"
            "5. Cauta dupa titlu\n"
            "6. Filtreaza\n"
            "7. Sorteaza\n"
            "0. Iesire\n";
}

string UIOld::citesteText(const string& mesaj) {
    cout << mesaj;
    string text;
    getline(cin >> std::ws, text);
    return text;
}

int UIOld::citesteInt(const string& mesaj) {
    cout << mesaj;
    int valoare;
    cin >> valoare;
    return valoare;
}

void UIOld::uiAdd() {
    const auto titlu = citesteText("Titlu: ");
    const auto gen = citesteText("Gen: ");
    const auto an = citesteInt("An: ");
    const auto actor = citesteText("Actor principal: ");
    service.serviceAdd(titlu, gen, an, actor);
}

void UIOld::uiDel() {
    const auto titlu = citesteText("Titlu de sters: ");
    service.serviceDel(titlu);
}

void UIOld::uiModify() {
    const auto titluVechi = citesteText("Titlu de modificat: ");
    const auto titluNou = citesteText("Titlu nou: ");
    const auto genNou = citesteText("Gen nou: ");
    const auto anNou = citesteInt("An nou: ");
    const auto actorNou = citesteText("Actor principal nou: ");
    service.serviceModify(titluVechi, titluNou, genNou, anNou, actorNou);
}

void UIOld::uiCauta() const {
    const auto titlu = citesteText("Titlu cautat: ");
    const int poz = service.serviceCauta(titlu);
    if (poz == -1) {
        cout << "Filmul nu exista.\n";
        return;
    }

    printFilm(service.serviceGetAll()[poz]);
}

void UIOld::uiShowAll() const {
    printLista(service.serviceGetAll());
}

void UIOld::uiFilter() const {
    const int optiune = citesteInt("Filtru 1=titlu 2=an: ");
    auto pattern = citesteText("Valoare: ");
    printLista(service.serviceFilter(optiune, pattern));
}

void UIOld::uiSort() const {
    const int optiune = citesteInt("Sortare 1=titlu 2=actor 3=an+gen: ");
    printLista(service.serviceSort(optiune));
}

void UIOld::run() {
    while (true) {
        printMeniu();
        const int cmd = citesteInt("Comanda: ");

        try {
            if (cmd == 0) {
                return;
            }
            if (cmd == 1) {
                uiAdd();
            } else if (cmd == 2) {
                uiDel();
            } else if (cmd == 3) {
                uiModify();
            } else if (cmd == 4) {
                uiShowAll();
            } else if (cmd == 5) {
                uiCauta();
            } else if (cmd == 6) {
                uiFilter();
            } else if (cmd == 7) {
                uiSort();
            } else {
                cout << "Comanda invalida.\n";
            }
        } catch (const std::exception& ex) {
            cout << ex.what() << '\n';
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
