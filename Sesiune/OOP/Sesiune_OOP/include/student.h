#pragma once

#include <string>

using std::string;

enum Facultate {
    info = 1,
    mate = 2,
    mateinfo = 3,
    ai = 4
};

class Student {
private:
    int nrmatricol;
    string nume;
    int varsta;
    Facultate facultate;

public:
    /* Construieste un student
    Input: nr, nme, vrst, fac
    Output: -
    Pre conditii: valorile primite pot descrie corect un student
    Post conditii: obiectul student este initializat
    */
    Student(int nr, string nme, int vrst, Facultate fac);

    /* Ofera numarul matricol al studentului
    Input: -
    Output: numarul matricol
    Pre conditii: obiectul student exista
    Post conditii: -
    */
    int getNrMatricol();

    /* Ofera numele studentului
    Input: -
    Output: numele studentului
    Pre conditii: obiectul student exista
    Post conditii: -
    */
    string getNume();

    /* Ofera varsta studentului
    Input: -
    Output: varsta studentului
    Pre conditii: obiectul student exista
    Post conditii: -
    */
    int getVarsta();

    /* Ofera facultatea studentului sub forma de text
    Input: -
    Output: facultatea studentului
    Pre conditii: obiectul student exista
    Post conditii: -
    */
    string getFacultate();

    /* Modifica numarul matricol al studentului
    Input: nr
    Output: -
    Pre conditii: obiectul student exista
    Post conditii: numarul matricol este actualizat
    */
    void setNrmatricol(int nr);

    /* Modifica numele studentului
    Input: nme
    Output: -
    Pre conditii: obiectul student exista
    Post conditii: numele este actualizat
    */
    void setNume(string nme);

    /* Modifica varsta studentului
    Input: vrst
    Output: -
    Pre conditii: obiectul student exista
    Post conditii: varsta este actualizata
    */
    void setVarsta(int vrst);

    /* Modifica facultatea studentului
    Input: fac
    Output: -
    Pre conditii: obiectul student exista
    Post conditii: facultatea este actualizata
    */
    void setFacultate(Facultate fac);
};
