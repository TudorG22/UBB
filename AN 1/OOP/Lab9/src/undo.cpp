#include "undo.h"

#include <utility>

UndoAdauga::UndoAdauga(Repo& repo, Film film)
    : repo(repo), filmAdaugat(std::move(film)) {
}

void UndoAdauga::doUndo() {
    repo.repoDel(filmAdaugat.getTitlu());
}

UndoSterge::UndoSterge(Repo& repo, Film film)
    : repo(repo), filmSters(std::move(film)) {
}

void UndoSterge::doUndo() {
    repo.repoAdd(filmSters);
}

UndoModifica::UndoModifica(Repo& repo, Film film, std::string titluNou)
    : repo(repo), filmVechi(std::move(film)), titluNou(std::move(titluNou)) {
}

void UndoModifica::doUndo() {
    repo.repoModify(titluNou, filmVechi);
}
