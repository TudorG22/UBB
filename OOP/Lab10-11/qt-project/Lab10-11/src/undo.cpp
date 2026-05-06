#include "undo.h"

#include <utility>

UndoAdauga::UndoAdauga(Repo& repo, Film film)
    : repo(repo), filmAdaugat(std::move(film)) {
}

void UndoAdauga::doUndo() {
    const int poz = repo.repoCauta(filmAdaugat.getTitlu());
    repo.repoDel(poz);
}

UndoSterge::UndoSterge(Repo& repo, Film film)
    : repo(repo), filmSters(std::move(film)) {
}

void UndoSterge::doUndo() {
    repo.repoAdd(filmSters.getTitlu(), filmSters.getGen(), filmSters.getAn(), filmSters.getActor());
}

UndoModifica::UndoModifica(Repo& repo, Film film, std::string titluNou)
    : repo(repo), filmVechi(std::move(film)), titluNou(std::move(titluNou)) {
}

void UndoModifica::doUndo() {
    const int poz = repo.repoCauta(titluNou);
    repo.repoModify(poz, filmVechi.getTitlu(), filmVechi.getGen(), filmVechi.getAn(), filmVechi.getActor());
}
