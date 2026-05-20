#pragma once

#include "domain.h"
#include "repo.h"
#include "error.h"

#include <vector>

class ServiceError : public AppError {
public:
    explicit ServiceError(const std::string& mesaj);
};

struct Comanda {
    Carte carte;
    int numarExemplare;
    int costTotal;
};

class Service {
private:
    Repo& repo;

public:
    explicit Service(Repo& r);

    static const char* const notFoundErrorMessage;
    static const char* const stockErrorMessage;

    int serviceCauta(int isbn) const;
    const std::vector<Carte>& serviceGetAll() const;
    const Carte& serviceGetCarteByIsbn(int isbn) const;
    std::vector<const Carte*> serviceFilterByGen(const std::string& gen) const;
    Comanda serviceCumpara(int isbn, int numarExemplare) const;
};
