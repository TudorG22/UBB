#pragma once

#include "service.h"

class UIOld {
private:
    Service& service;

    static void printFilm(const Film& film);
    static void printLista(const vector<Film>& filme);
    static void printLista(const vector<const Film*>& filme);
    static void printMeniu();

    static std::string citesteText(const std::string& mesaj);
    static int citesteInt(const std::string& mesaj);

    void uiAdd();
    void uiDel();
    void uiModify();
    void uiCauta() const;
    void uiShowAll() const;
    void uiFilter() const;
    void uiSort() const;

public:
    explicit UIOld(Service& service);
    void run();
};
