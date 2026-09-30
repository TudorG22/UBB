#include "service/service_cheltuieli.h"

ServiceCheltuieli service_creeaza(RepoCheltuieli* repo) {
    ServiceCheltuieli service;
    service.repo = repo;
    return service;
}

size_t service_numar_cheltuieli(const ServiceCheltuieli* service) {
    return repo_dimensiune(service->repo);
}

const VectorDinamic* service_lista(const ServiceCheltuieli* service) {
    return repo_toate(service->repo);
}

int service_adauga_cheltuiala(ServiceCheltuieli* service, int zi, double suma, TipCheltuiala tip) {
    repo_adauga(service->repo, cheltuiala_creeaza(zi, suma, tip));
    return 0;
}

int service_modifica_cheltuiala(ServiceCheltuieli* service, size_t index, int zi, double suma, TipCheltuiala tip) {
    repo_modifica(service->repo, index, cheltuiala_creeaza(zi, suma, tip));
    return 0;
}

int service_sterge_cheltuiala(ServiceCheltuieli* service, size_t index) {
    repo_sterge(service->repo, index);
    return 0;
}

VectorDinamic service_filtreaza_dupa_tip(const ServiceCheltuieli* service, TipCheltuiala tip) {
    VectorDinamic rezultat = vector_dinamic_creeaza(sizeof(Cheltuiala));
    size_t n = repo_dimensiune(service->repo);

    for (size_t i = 0; i < n; i++) {
        Cheltuiala c = repo_get(service->repo, i);
        if (c.tip == tip) {
            vector_dinamic_adauga(&rezultat, &c);
        }
    }

    return rezultat;
}

VectorDinamic service_filtreaza_dupa_zi(const ServiceCheltuieli* service, int zi) {
    VectorDinamic rezultat = vector_dinamic_creeaza(sizeof(Cheltuiala));
    size_t n = repo_dimensiune(service->repo);

    for (size_t i = 0; i < n; i++) {
        Cheltuiala c = repo_get(service->repo, i);
        if (c.zi == zi) {
            vector_dinamic_adauga(&rezultat, &c);
        }
    }

    return rezultat;
}

VectorDinamic service_filtreaza_dupa_suma_minima(const ServiceCheltuieli* service, double suma_minima) {
    VectorDinamic rezultat = vector_dinamic_creeaza(sizeof(Cheltuiala));
    size_t n = repo_dimensiune(service->repo);

    for (size_t i = 0; i < n; i++) {
        Cheltuiala c = repo_get(service->repo, i);
        if (c.suma >= suma_minima) {
            vector_dinamic_adauga(&rezultat, &c);
        }
    }

    return rezultat;
}

void service_sorteaza(VectorDinamic* cheltuieli, int crescator, ServiceSortCheie cheie) {
    if (cheie != SERVICE_SORT_CHEIE_SUMA && cheie != SERVICE_SORT_CHEIE_TIP) {
        return;
    }

    size_t n = vector_dinamic_dimensiune(cheltuieli);

    for (size_t i = 0; i + 1 < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            Cheltuiala* a = (Cheltuiala*)vector_dinamic_get(cheltuieli, i);
            Cheltuiala* b = (Cheltuiala*)vector_dinamic_get(cheltuieli, j);
            int trebuie_swap = 0;

            if (cheie == SERVICE_SORT_CHEIE_SUMA) {
                trebuie_swap = crescator ? (a->suma > b->suma) : (a->suma < b->suma);
            } else if (cheie == SERVICE_SORT_CHEIE_TIP) {
                trebuie_swap = crescator ? (a->tip > b->tip) : (a->tip < b->tip);
            }

            if (trebuie_swap) {
                Cheltuiala aux = *a;
                *a = *b;
                *b = aux;
            }
        }
    }
}
