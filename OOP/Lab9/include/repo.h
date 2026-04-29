#pragma once 

#include "domain.h"
#include "validator.h"
#include <map>
#include <vector>

using std::string;

class RepoError : public AppError {
public:
    explicit RepoError(const std::string& mesaj);
};

class Repo {
public:
    virtual ~Repo() = default;

    virtual int repoDim() const = 0;
    virtual void repoAdd(const Film& film) = 0;
    virtual bool repoExista(const string& titlu) const = 0;
    virtual const Film& repoFind(const string& titlu) const = 0;
    virtual void repoDel(const string& titlu) = 0;
    virtual void repoModify(const string& titluVechi, const Film& filmNou) = 0;
    virtual const std::vector<Film>& repoGetAll() const = 0;
};

// ---------------------------------------
class RepoVector : public Repo {
private:
        std::vector<Film> date;

public:
    RepoVector() = default;

    int repoDim() const override;
    void repoAdd(const Film& film) override;
    bool repoExista(const string& titlu) const override;
    const Film& repoFind(const string& titlu) const override;
    void repoDel(const string& titlu) override;
    void repoModify(const string& titluVechi, const Film& filmNou) override;
    const std::vector<Film>& repoGetAll() const override;
};

// ---------------------------------------
class RepoMap : public Repo {
private:
    std::map<string, Film> date;
    mutable std::vector<Film> temp;

    void rebuildCache() const;

public:
    RepoMap() = default;

    int repoDim() const override;
    void repoAdd(const Film& film) override;
    bool repoExista(const string& titlu) const override;
    const Film& repoFind(const string& titlu) const override;
    void repoDel(const string& titlu) override;
    void repoModify(const string& titluVechi, const Film& filmNou) override;
    const std::vector<Film>& repoGetAll() const override;
};
