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
    /* Creeaza service-ul aplicatiei
    Input: r
    Output: -
    Pre conditii: repository-ul este initializat
    Post conditii: service-ul este gata de folosire
    */
    explicit Service(Repo& r);

    static const char* const notFoundErrorMessage;
    static const char* const stockErrorMessage;

    /* Cauta o carte dupa isbn
    Input: isbn
    Output: -1 daca nu exista, pozitia ei daca exista
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    int serviceCauta(int isbn) const;

    /* Ofera toate cartile disponibile
    Input: -
    Output: colectia de carti
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    const std::vector<Carte>& serviceGetAll() const;

    /* Returneaza cartea corespunzatoare unui isbn
    Input: isbn
    Output: cartea cautata
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    const Carte& serviceGetCarteByIsbn(int isbn) const;

    /* Filtreaza cartile dupa gen
    Input: gen
    Output: cartile care apartin genului dat
    Pre conditii: service-ul este initializat
    Post conditii: -
    */
    std::vector<const Carte*> serviceFilterByGen(const std::string& gen) const;

    /* Verifica o comanda de cumparare
    Input: isbn, numarExemplare
    Output: detaliile comenzii si costul total
    Pre conditii: service-ul este initializat
    Post conditii: comanda este calculata daca datele sunt valide
    */
    Comanda serviceCumpara(int isbn, int numarExemplare) const;
};
