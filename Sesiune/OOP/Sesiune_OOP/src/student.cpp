#include "../include/student.h"

Student::Student(int nr, string nme, int vrst, Facultate fac)
    : nrmatricol(nr), nume(nme), varsta(vrst), facultate(fac) {}

int Student::getNrMatricol() {
    return nrmatricol;
}

string Student::getNume() {
    return nume;
}

int Student::getVarsta() {
    return varsta;
}

string Student::getFacultate() {
    if (facultate == info) {
        return "info";
    }
    if (facultate == mate) {
        return "mate";
    }
    if (facultate == mateinfo) {
        return "mateinfo";
    }
    if (facultate == ai) {
        return "ai";
    }
    return "";
}

void Student::setNrmatricol(int nr) {
    nrmatricol = nr;
}

void Student::setNume(string nme) {
    nume = nme;
}

void Student::setVarsta(int vrst) {
    varsta = vrst;
}

void Student::setFacultate(Facultate fac) {
    facultate = fac;
}
