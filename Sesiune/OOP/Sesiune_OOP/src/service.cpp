#include "../include/service.h"

namespace {
void modificaToateVarstele(Repo& repo, int diferenta) {
    std::vector<Student> lista = repo.repoGetAll();

    for (int i = 0; i < lista.size(); i++) {
        Student stud = lista[i];
        repo.repoSetVarstaStud(stud, stud.getVarsta() + diferenta);
    }
}
}

Service::Service(Repo& r)
    : repo(r) {
}

int Service::serviceCauta(int nrmat) {
    return repo.repoCauta(nrmat);
}

std::vector<Student> Service::serviceGetAll() {
    return repo.repoGetAll();
}

std::vector<Student> Service::serviceSortByVarsta() {
    std::vector<Student> lista = repo.repoGetAll();

    for (int i = 0; i < lista.size(); i++) {
        for (int j = i + 1; j < lista.size(); j++) {
            if (lista[i].getVarsta() > lista[j].getVarsta()) {
                Student aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }

    return lista;
}

void Service::intinerire() {
    modificaToateVarstele(repo, -1);

    Undo u;
    u.actiune = 1;
    undoMemory.push_back(u);
}

void Service::imbatrinire() {
    modificaToateVarstele(repo, 1);

    Undo u;
    u.actiune = 2;
    undoMemory.push_back(u);
}

void Service::stergeStudent(Student& stud) {
    repo.stergeStudentRepo(stud);

    Undo u;
    u.actiune = 3;
    u.studenti.push_back(stud);
    undoMemory.push_back(u);
}

void Service::doUndo() {
    if (undoMemory.empty()) {
        return;
    }

    Undo u = undoMemory.back();
    undoMemory.pop_back();

    if (u.actiune == 1) {
        modificaToateVarstele(repo, 1);
    } else if (u.actiune == 2) {
        modificaToateVarstele(repo, -1);
    } else if (u.actiune == 3) {
        repo.repoAdaugaStudent(u.studenti[0]);
    }

    redoMemory.push_back(u);
}

void Service::doRedo() {
    if (redoMemory.empty()) {
        return;
    }

    Undo u = redoMemory.back();
    redoMemory.pop_back();

    if (u.actiune == 1) {
        modificaToateVarstele(repo, -1);
    } else if (u.actiune == 2) {
        modificaToateVarstele(repo, 1);
    } else if (u.actiune == 3) {
        repo.stergeStudentRepo(u.studenti[0]);
    }

    undoMemory.push_back(u);
}
