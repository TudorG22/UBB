#pragma once

#include <vector>

#include "student.h"
#include "repo.h"

using std::vector;

struct Undo {
    int actiune;
    vector<Student> studenti;
};

class Service {
private:
    Repo& repo;
    vector<Undo> undoMemory;
    vector<Undo> redoMemory;

public:
    /* Creeaza service-ul aplicatiei
    Input: r
    Output: -
    Pre conditii: repository-ul este initializat
    Post conditii: service-ul este gata de folosire
    */
    Service(Repo& r);

    /* Cauta un student dupa numarul matricol
    Input: nrmat
    Output: -1 daca nu exista, pozitia lui daca exista
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    int serviceCauta(int nrmat);

    /* Returneaza toti studentii 
    Input: -
    Output: vectorul de studenti
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    std::vector<Student> serviceGetAll();

    /* Returneaza studentii sortati crescator dupa varsta
    Input: -
    Output: vectorul de studenti sortat dupa varsta
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    std::vector<Student> serviceSortByVarsta();

    /* Micsoreaza cu 1 varsta tuturor studentilor
    Input: -
    Output: -
    Pre conditii: service-ul este initializat
    Post conditii: varsta fiecarui student este scazuta cu 1
    */
    void intinerire();

    /* Mareste cu 1 varsta tuturor studentilor
    Input: -
    Output: -
    Pre conditii: service-ul este initializat
    Post conditii: varsta fiecarui student este crescuta cu 1
    */
    void imbatrinire();

    /* Sterge un student prin service
    Input: stud
    Output: -
    Pre conditii: service-ul este initializat
    Post conditii: studentul este sters daca exista
    */
    void stergeStudent(Student& stud);

    /* Reface invers ultima operatie salvata
    Input: -
    Output: -
    Pre conditii: service-ul este initializat
    Post conditii: ultima operatie este anulata daca exista
    */
    void doUndo();

    /* Reaplica ultima operatie anulata
    Input: -
    Output: -
    Pre conditii: service-ul este initializat
    Post conditii: ultima operatie anulata este refacuta daca exista
    */
    void doRedo();
};
