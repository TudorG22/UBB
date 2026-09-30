#pragma once

#include "repo.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Repo& repo;
    Film filmAdaugat;

public:
    UndoAdauga(Repo& repo, Film film);
    void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
private:
    Repo& repo;
    Film filmSters;

public:
    UndoSterge(Repo& repo, Film film);
    void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
private:
    Repo& repo;
    Film filmVechi;
    std::string titluNou;

public:
    UndoModifica(Repo& repo, Film film, std::string titluNou);
    void doUndo() override;
};
