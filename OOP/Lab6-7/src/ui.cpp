#include "ui.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

UI::UI(Service& service) : service(service) {
}

void UI::clearScreen() {
    cout << "\033[2J\033[H";
}

void UI::moveCursor(int row, int col) {
    cout << "\033[" << row << ';' << col << 'H';
}

void UI::clearFromCursor() {
    cout << "\033[J";
}

void UI::clearLine() {
    cout << "\033[2K\r";
}

string UI::citesteText(const string& mesaj) {
    cout << mesaj;
    string text;
    getline(cin >> std::ws, text);
    return text;
}

int UI::citesteInt(const string& mesaj) {
    cout << mesaj;
    int valoare;
    cin >> valoare;
    return valoare;
}

string UI::filmToString(const Film& film) {
    std::ostringstream out;
    out << film.getTitlu() << " | "
        << film.getGen() << " | "
        << film.getAn() << " | "
        << film.getActor();
    return out.str();
}

string UI::listaToString(const VectorDinamic<Film>& filme) {
    if (filme.empty()) {
        return "Nu exista filme.\n";
    }

    std::ostringstream out;
    for (const auto& film : filme) {
        out << filmToString(film) << '\n';
    }
    return out.str();
}

string UI::listaToString(const VectorDinamic<const Film*>& filme) {
    if (filme.empty()) {
        return "Nu exista filme.\n";
    }

    std::ostringstream out;
    for (const auto film : filme) {
        out << filmToString(*film) << '\n';
    }
    return out.str();
}

void UI::drawStaticScreen() const {
    clearScreen();
    cout << "1. Adauga\n"
            "2. Sterge\n"
            "3. Modifica\n"
            "4. Afiseaza toate\n"
            "5. Cauta dupa titlu\n"
            "6. Filtreaza\n"
            "7. Sorteaza\n"
            "0. Iesire\n"
            "\n"
            "Input:\n"
            "\n"
            "Rezultat:\n";
    showOutput("Aplicatia a pornit.\n");
}

void UI::clearInputArea() const {
    for (int row = inputRow; row <= outputRow - 1; ++row) {
        moveCursor(row, 1);
        clearLine();
    }
    moveCursor(inputRow, 1);
}

void UI::showOutput(const string& text) const {
    moveCursor(outputRow, 1);
    clearFromCursor();
    cout << text;
    cout.flush();
}

void UI::uiAdd() const {
    const auto titlu = citesteText("Titlu: ");
    const auto gen = citesteText("Gen: ");
    const auto an = citesteInt("An: ");
    const auto actor = citesteText("Actor principal: ");
    service.serviceAdd(titlu, gen, an, actor);
    showOutput("Film adaugat.\n");
}

void UI::uiDel() const {
    const auto titlu = citesteText("Titlu de sters: ");
    service.serviceDel(titlu);
    showOutput("Operatie finalizata.\n");
}

void UI::uiModify() const {
    const auto titluVechi = citesteText("Titlu de modificat: ");
    const auto titluNou = citesteText("Titlu nou: ");
    const auto genNou = citesteText("Gen nou: ");
    const auto anNou = citesteInt("An nou: ");
    const auto actorNou = citesteText("Actor principal nou: ");
    service.serviceModify(titluVechi, titluNou, genNou, anNou, actorNou);
    showOutput("Film modificat.\n");
}

void UI::uiCauta() const {
    const auto titlu = citesteText("Titlu cautat: ");
    const int poz = service.serviceCauta(titlu);
    if (poz == -1) {
        showOutput("Filmul nu exista.\n");
        return;
    }

    showOutput(filmToString(service.serviceGetAll()[poz]) + '\n');
}

void UI::uiShowAll() const {
    showOutput(listaToString(service.serviceGetAll()));
}

void UI::uiFilter() const {
    const int optiune = citesteInt("Filtru 1=titlu 2=an: ");
    auto pattern = citesteText("Valoare: ");
    showOutput(listaToString(service.serviceFilter(optiune, pattern)));
}

void UI::uiSort() const {
    const int optiune = citesteInt("Sortare 1=titlu 2=actor 3=an+gen: ");
    showOutput(listaToString(service.serviceSort(optiune)));
}

void UI::run() const {
    drawStaticScreen();

    while (true) {
        clearInputArea();

        try {
            const int cmd = citesteInt("Comanda: ");

            if (cmd == 0) {
                moveCursor(outputRow, 1);
                clearFromCursor();
                cout << "La revedere.\n";
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
                showOutput("Comanda invalida.\n");
            }
        } catch (const std::exception& ex) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            showOutput(string("Eroare: ") + ex.what() + '\n');
        }
    }
}
