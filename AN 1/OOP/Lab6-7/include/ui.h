#pragma once

#include "service.h"

#include <string>

class UI {
private:
    Service& service;

    static constexpr int inputRow = 10;
    static constexpr int outputRow = 15;

    static void clearScreen();
    static void moveCursor(int row, int col);
    static void clearFromCursor();
    static void clearLine();

    static std::string citesteText(const std::string& mesaj);
    static int citesteInt(const std::string& mesaj);

    static std::string filmToString(const Film& film);
    static std::string listaToString(const VectorDinamic<Film>& filme);
    static std::string listaToString(const VectorDinamic<const Film*>& filme);

    void drawStaticScreen() const;
    void clearInputArea() const;
    void showOutput(const std::string& text) const;

    void uiAdd() const;
    void uiDel() const;
    void uiModify() const;
    void uiCauta() const;
    void uiShowAll() const;
    void uiFilter() const;
    void uiSort() const;

public:
    explicit UI(Service& service);
    void run() const;
};
