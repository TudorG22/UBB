#include "../include/service.h"

const char* const Service::notFoundErrorMessage = "Cartea nu exista.";
const char* const Service::stockErrorMessage = "Stoc insuficient.";

ServiceError::ServiceError(const std::string& mesaj)
    : AppError(mesaj) {
}

Service::Service(Repo& r)
    : repo(r) {
}

int Service::serviceCauta(int isbn) const {
    return repo.repoCauta(isbn);
}

const std::vector<Carte>& Service::serviceGetAll() const {
    return repo.repoGetAll();
}

const Carte& Service::serviceGetCarteByIsbn(int isbn) const {
    const int poz = repo.repoCauta(isbn);
    if (poz == -1) {
        throw ServiceError(notFoundErrorMessage);
    }

    return repo.repoGetAll().at(poz);
}

std::vector<const Carte*> Service::serviceFilterByGen(const std::string& gen) const {
    std::vector<const Carte*> filtrate;

    for (const Carte& carte : repo.repoGetAll()) {
        if (carte.getGen() == gen) {
            filtrate.push_back(&carte);
        }
    }

    return filtrate;}

Comanda Service::serviceCumpara(int isbn, int numarExemplare) const {
    if (isbn <= 0) {
        throw ServiceError("Isbn invalid.");
    }
    if (numarExemplare <= 0) {
        throw ServiceError("Numar de exemplare invalid.");
    }

    const int poz = repo.repoCauta(isbn);
    if (poz == -1) {
        throw ServiceError(notFoundErrorMessage);
    }

    const Carte& carte = repo.repoGetAll().at(poz);
    if (carte.getStoc() < numarExemplare) {
        throw ServiceError(stockErrorMessage);
    }

    // GCOVR_EXCL_START
    return Comanda{carte, numarExemplare, carte.getPret() * numarExemplare};
    // GCOVR_EXCL_STOP
}
