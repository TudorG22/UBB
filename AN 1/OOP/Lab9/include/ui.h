#pragma once

#include "service.h"

#include <string>
#include <vector>

class UIError : public AppError {
public:
    explicit UIError(const std::string& mesaj);
};

class UI {
private:
    Service& service;
    std::string repoType;
    bool useDate;

    static const int inputRow = 19;
    static const int outputRow = 25;

    static void clearScreen();
    static void moveCursor(int row, int col);
    static void clearFromCursor();
    static void clearLine();

    static std::string citesteText(const std::string& mesaj);
    static int citesteInt(const std::string& mesaj);

    static std::string filmToString(const Film& film);
    static std::string listaToString(const std::vector<Film>& filme);
    static std::string listaToString(const std::vector<const Film*>& filme);
    static std::string mapToString(const std::map<std::string, int>& raport);

    void drawStaticScreen() const;
    void clearInputArea() const;
    void showOutput(const std::string& text) const;

    void uiAdd() const;
    void uiDel() const;
    void uiModify() const;
    void uiUndo() const;
    void uiCauta() const;
    void uiShowAll() const;
    void uiFilter() const;
    void uiSort() const;
    void uiRaportGenuri() const;
    void uiCosGoleste() const;
    void uiCosAdauga() const;
    void uiCosGenereaza() const;
    void uiCosAfiseaza() const;
    void uiCosSalveaza() const;
    void uiRepoSalveaza() const;

public:
    UI(Service& service, const std::string& repoType, bool useDate);
    void run() const;
};
