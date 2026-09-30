#include "../include/repo.h"

#include <fstream>
#include <sstream>

Facultate stringToFacultate(string facultate) {
    if (facultate == "info") {
        return info;
    }
    if (facultate == "mate") {
        return mate;
    }
    if (facultate == "mateinfo") {
        return mateinfo;
    }
    return ai;
}

Repo::Repo(string numeFisier) {
    this->numeFisier = numeFisier;
    incarcaDinFisier();
}

int Repo::repoDim() {
    return Studneti.size();
}

int Repo::repoCauta(int nrmat) {
    for (int i = 0; i < Studneti.size(); i++) {
        if (Studneti[i].getNrMatricol() == nrmat) {
            return i;
        }
    }
    return -1;
}

vector<Student>& Repo::repoGetAll() {
    return Studneti;
}

void Repo::repoAdaugaStudent(Student& stud) {
    Studneti.push_back(stud);
    salveazaInFisier();
}

void Repo::incarcaDinFisier() {
    Studneti.clear();

    std::ifstream fin(numeFisier);
    if (!fin.is_open()) {
        return;
    }

    string linie;
    while (getline(fin, linie)) {
        if (linie == "") {
            continue;
        }

        std::stringstream ss(linie);
        string nr;
        string nume;
        string varsta;
        string facultate;

        getline(ss, nr, ',');
        getline(ss, nume, ',');
        getline(ss, varsta, ',');
        getline(ss, facultate, ',');

        Student s(stoi(nr), nume, stoi(varsta), stringToFacultate(facultate));
        Studneti.push_back(s);
    }

    fin.close();
}

void Repo::salveazaInFisier() {
    std::ofstream fout(numeFisier);

    for (int i = 0; i < Studneti.size(); i++) {
        fout << Studneti[i].getNrMatricol() << ",";
        fout << Studneti[i].getNume() << ",";
        fout << Studneti[i].getVarsta() << ",";
        fout << Studneti[i].getFacultate() << "\n";
    }

    fout.close();
}

void Repo::stergeStudentRepo(Student& stud) {
    int poz = repoCauta(stud.getNrMatricol());
    if (poz != -1) {
        Studneti.erase(Studneti.begin() + poz);
        salveazaInFisier();
    }
}

int Repo::repoGetVarstaStud(Student& stud) {
    int poz = repoCauta(stud.getNrMatricol());
    if (poz != -1) {
        return Studneti[poz].getVarsta();
    }
    return -1;
}

void Repo::repoSetVarstaStud(Student& stud, int varsta) {
    int poz = repoCauta(stud.getNrMatricol());
    if (poz != -1) {
        Studneti[poz].setVarsta(varsta);
        salveazaInFisier();
    }
}
