#pragma once

#include <vector>
#include "student.h"

using std::string;
using std::vector;

class Repo {
private:
    vector<Student> Studneti;
    string numeFisier;

    /* Incarca studentii din fisier
    Input: -
    Output: -
    Pre conditii: numele fisierului este setat
    Post conditii: studentii din fisier sunt memorati in repository
    */
    void incarcaDinFisier();

    /* Salveaza studentii in fisier
    Input: -
    Output: -
    Pre conditii: repository-ul exista
    Post conditii: continutul repository-ului este scris in fisier
    */
    void salveazaInFisier();

public:
    /* Construieste repository-ul de studenti
    Input: numeFisier
    Output: -
    Pre conditii: numele fisierului este valid
    Post conditii: repository-ul este pregatit pentru utilizare
    */
    Repo(string numeFisier = "repo.txt");

    /* Returneaza numarul de studenti din repository
    Input: -
    Output: numarul de studenti
    Pre conditii: repository-ul exista
    Post conditii: -
    */
    int repoDim();

    /* Cauta pozitia unui student dupa numarul matricol
    Input: nrmat
    Output: -1 daca nu exista, pozitia lui daca exista
    Pre conditii: repository-ul exista
    Post conditii: -
    */
    int repoCauta(int nrmat);

    /* Returneaza toti studentii din repository
    Input: -
    Output: colectia de studenti
    Pre conditii: repository-ul exista
    Post conditii: -
    */
    vector<Student>& repoGetAll();

    /* Adauga un student in repository
    Input: stud
    Output: -
    Pre conditii: studentul este initializat
    Post conditii: studentul este adaugat si fisierul este actualizat
    */
    void repoAdaugaStudent(Student& stud);

    /* Sterge un student din repository
    Input: stud
    Output: -
    Pre conditii: studentul este initializat
    Post conditii: studentul este sters daca exista si fisierul este actualizat
    */
    void stergeStudentRepo(Student& stud);

    /* Returneaza varsta unui student din repository
    Input: stud
    Output: varsta studentului sau -1 daca nu exista
    Pre conditii: studentul este initializat
    Post conditii: -
    */
    int repoGetVarstaStud(Student& stud);

    /* Modifica varsta unui student din repository
    Input: stud, varsta
    Output: -
    Pre conditii: studentul este initializat
    Post conditii: varsta este actualizata daca studentul exista
    */
    void repoSetVarstaStud(Student& stud, int varsta);
};
