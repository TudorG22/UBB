#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "../include/student.h"
#include "../include/repo.h"
#include "../include/service.h"

void testStudent() {
    Student stud(10, "Ana", 20, info);

    assert(stud.getNrMatricol() == 10);
    assert(stud.getNume() == "Ana");
    assert(stud.getVarsta() == 20);
    assert(stud.getFacultate() == "info");

    stud.setNrmatricol(11);
    stud.setNume("Maria");
    stud.setVarsta(21);
    stud.setFacultate(mate);

    assert(stud.getNrMatricol() == 11);
    assert(stud.getNume() == "Maria");
    assert(stud.getVarsta() == 21);
    assert(stud.getFacultate() == "mate");
}

void testRepo() {
    std::ofstream fout("test/repo_test.txt");
    fout << "1,Ana,20,info\n";
    fout << "2,Maria,22,mate\n";
    fout.close();

    Repo repo("test/repo_test.txt");
    Student studNou(3, "Ioan", 19, ai);
    Student studCautat(1, "Ana", 20, info);

    assert(repo.repoDim() == 2);
    assert(repo.repoCauta(2) == 1);
    assert(repo.repoGetVarstaStud(studCautat) == 20);

    repo.repoAdaugaStudent(studNou);
    assert(repo.repoDim() == 3);
    assert(repo.repoCauta(3) == 2);

    repo.repoSetVarstaStud(studNou, 25);
    assert(repo.repoGetVarstaStud(studNou) == 25);

    repo.stergeStudentRepo(studNou);
    assert(repo.repoDim() == 2);
    assert(repo.repoCauta(3) == -1);
}

void testService() {
    std::ofstream fout("test/service_test.txt");
    fout << "1,Ana,20,info\n";
    fout << "2,Maria,22,mate\n";
    fout.close();

    Repo repo("test/service_test.txt");
    Service service(repo);
    Student studSters(1, "Ana", 20, info);

    assert(service.serviceCauta(2) == 1);
    assert(service.serviceSortByVarsta()[0].getVarsta() == 20);

    service.intinerire();
    assert(service.serviceGetAll()[0].getVarsta() == 19);
    assert(service.serviceGetAll()[1].getVarsta() == 21);

    service.imbatrinire();
    assert(service.serviceGetAll()[0].getVarsta() == 20);
    assert(service.serviceGetAll()[1].getVarsta() == 22);

    service.stergeStudent(studSters);
    assert(service.serviceCauta(1) == -1);

    service.doUndo();
    assert(service.serviceCauta(1) != -1);

    service.doRedo();
    assert(service.serviceCauta(1) == -1);
}

int main() {
    std::cout << "Rulare teste...\n";
    testStudent();
    testRepo();
    testService();
    std::cout << "Toate testele au trecut.\n";
    return 0;
}
