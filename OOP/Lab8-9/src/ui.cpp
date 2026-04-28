#include "ui.h"

#include <iostream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

namespace {
constexpr int cmdExit = 0;
constexpr int cmdAdd = 1;
constexpr int cmdDelete = 2;
constexpr int cmdModify = 3;
constexpr int cmdShowAll = 4;
constexpr int cmdSearch = 5;
constexpr int cmdFilter = 6;
constexpr int cmdSort = 7;
constexpr int cmdReportGenres = 8;
constexpr int cmdCartEmpty = 9;
constexpr int cmdCartAdd = 10;
constexpr int cmdCartGenerate = 11;
constexpr int cmdCartShow = 12;
}

UI::UI(Service& service) : service(service) {
}

UIError::UIError(const std::string& mesaj)
    : AppError(mesaj) {
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
    string text;
    getline(cin >> std::ws, text);

    std::istringstream in(text);
    int valoare = 0;
    char extra = '\0';
    if (!(in >> valoare) || (in >> extra)) {
        throw UIError("Input invalid.");
    }

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

string UI::listaToString(const std::vector<Film>& filme) {
    if (filme.empty()) {
        return "Nu exista filme.\n";
    }

    std::ostringstream out;
    for (const Film& film : filme) {
        out << filmToString(film) << '\n';
    }
    return out.str();
}

string UI::listaToString(const std::vector<const Film*>& filme) {
    if (filme.empty()) {
        return "Nu exista filme.\n";
    }

    std::ostringstream out;
    for (const Film* film : filme) {
        out << filmToString(*film) << '\n';
    }
    return out.str();
}

string UI::mapToString(const std::map<string, int>& raport) {
    if (raport.empty()) {
        return "Nu exista filme.\n";
    }

    std::ostringstream out;
    for (const std::pair<const string, int>& pereche : raport) {
        out << pereche.first << " | " << pereche.second << '\n';
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
            "8. Raport genuri\n"
            "9. Goleste cos\n"
            "10. Adauga in cos\n"
            "11. Genereaza cos\n"
            "12. Afiseaza cos\n"
            "0. Iesire\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "Rezultat:\n";
    showOutput("Aplicatia a pornit.\n");
}

void UI::clearInputArea() const {
    for (int row = inputRow; row <= outputRow - 2; ++row) {
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
    const string titlu = citesteText("Titlu: ");
    const string gen = citesteText("Gen: ");
    const int an = citesteInt("An: ");
    const string actor = citesteText("Actor principal: ");
    service.serviceAdd(titlu, gen, an, actor);
    showOutput("Film adaugat.\n");
}

void UI::uiDel() const {
    const string titlu = citesteText("Titlu de sters: ");
    service.serviceDel(titlu);
    showOutput("Operatie finalizata.\n");
}

void UI::uiModify() const {
    const string titluVechi = citesteText("Titlu de modificat: ");
    const string titluNou = citesteText("Titlu nou: ");
    const string genNou = citesteText("Gen nou: ");
    const int anNou = citesteInt("An nou: ");
    const string actorNou = citesteText("Actor principal nou: ");
    service.serviceModify(titluVechi, titluNou, genNou, anNou, actorNou);
    showOutput("Film modificat.\n");
}

void UI::uiCauta() const {
    const string titlu = citesteText("Titlu cautat: ");
    const int poz = service.serviceCauta(titlu);
    if (poz == -1) {
        showOutput("Filmul nu exista.\n");
        return;
    }

    showOutput(filmToString(service.serviceGetAll().at(static_cast<std::size_t>(poz))) + '\n');
}

void UI::uiShowAll() const {
    showOutput(listaToString(service.serviceGetAll()));
}

void UI::uiFilter() const {
    const int optiune = citesteInt("Filtru 1=titlu 2=an: ");
    if (optiune != 1 && optiune != 2) {
        throw UIError("Optiune invalida.");
    }

    const string pattern = citesteText("Valoare: ");
    showOutput(listaToString(service.serviceFilter(optiune, pattern)));
}

void UI::uiSort() const {
    const int optiune = citesteInt("Sortare 1=titlu 2=actor 3=an+gen: ");
    if (optiune != 1 && optiune != 2 && optiune != 3) {
        throw UIError("Optiune invalida.");
    }

    showOutput(listaToString(service.serviceSort(optiune)));
}

void UI::uiRaportGenuri() const {
    showOutput(mapToString(service.raportGenuri()));
}

void UI::uiCosGoleste() const {
    service.cosGoleste();
    showOutput("Cos golit.\n");
}

void UI::uiCosAdauga() const {
    const string titlu = citesteText("Titlu de adaugat in cos: ");
    service.cosAdauga(titlu);
    showOutput(listaToString(service.cosGetAll()));
}

void UI::uiCosGenereaza() const {
    const int numarFilme = citesteInt("Numar filme in cos: ");
    service.cosGenereaza(numarFilme);
    showOutput(listaToString(service.cosGetAll()));
}

void UI::uiCosAfiseaza() const {
    showOutput(listaToString(service.cosGetAll()));
}

void UI::run() const {
    drawStaticScreen();

    while (true) {
        clearInputArea();

        try {
            const int cmd = citesteInt("Comanda: ");
            clearInputArea();

            if (cmd == cmdExit) {
                moveCursor(outputRow, 1);
                clearFromCursor();
                cout << "La revedere.\n";
                return;
            }
            if (cmd == cmdAdd) {
                uiAdd();
            } else if (cmd == cmdDelete) {
                uiDel();
            } else if (cmd == cmdModify) {
                uiModify();
            } else if (cmd == cmdShowAll) {
                uiShowAll();
            } else if (cmd == cmdSearch) {
                uiCauta();
            } else if (cmd == cmdFilter) {
                uiFilter();
            } else if (cmd == cmdSort) {
                uiSort();
            } else if (cmd == cmdReportGenres) {
                uiRaportGenuri();
            } else if (cmd == cmdCartEmpty) {
                uiCosGoleste();
            } else if (cmd == cmdCartAdd) {
                uiCosAdauga();
            } else if (cmd == cmdCartGenerate) {
                uiCosGenereaza();
            } else if (cmd == cmdCartShow) {
                uiCosAfiseaza();
            } else {
                showOutput("Comanda invalida.\n");
            }
        } catch (const std::exception& ex) {
            showOutput(string("Eroare: ") + ex.what() + '\n');
        }
    }
}
