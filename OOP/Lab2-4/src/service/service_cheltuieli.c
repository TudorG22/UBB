#include "service/service_cheltuieli.h"
#include <stdlib.h>

static void service_salveaza_snapshot(ServiceCheltuieli* service);
static void service_distruge_snapshot(VectorDinamic* snapshot);

ServiceCheltuieli service_creeaza(RepoCheltuieli* repo) {
    ServiceCheltuieli service;
    service.repo = repo;
    service.undo_list = vector_dinamic_creeaza();
    return service;
}

size_t service_numar_cheltuieli(const ServiceCheltuieli* service) {
    return repo_dimensiune(service->repo);
}


const VectorDinamic* service_lista(const ServiceCheltuieli* service) {
    return repo_toate(service->repo);
}

int service_adauga_cheltuiala(ServiceCheltuieli* service, int zi, double suma, TipCheltuiala tip) {
    Cheltuiala cheltuiala = cheltuiala_creeaza(zi, suma, tip);
    service_salveaza_snapshot(service);
    repo_adauga(service->repo, &cheltuiala);

    return 0;
}

int service_modifica_cheltuiala(ServiceCheltuieli* service, size_t index, int zi, double suma, TipCheltuiala tip) {
    Cheltuiala cheltuiala_noua = cheltuiala_creeaza(zi, suma, tip);
    service_salveaza_snapshot(service);
    repo_modifica(service->repo, index, &cheltuiala_noua);
    return 0;
}

int service_sterge_cheltuiala(ServiceCheltuieli* service, size_t index) {
    service_salveaza_snapshot(service);
    repo_sterge(service->repo, index);
    return 0;
}

VectorDinamic service_filtreaza_dupa_tip(const ServiceCheltuieli* service, TipCheltuiala tip) {
    VectorDinamic rezultat = vector_dinamic_creeaza();
    const VectorDinamic* toate = repo_toate(service->repo);
    size_t n = vector_dinamic_dimensiune(toate);

    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(toate, i);
        if (c->tip == tip) {
            vector_dinamic_adauga(&rezultat, (void*)c);
        }
    }

    return rezultat;
}

VectorDinamic service_filtreaza_dupa_zi(const ServiceCheltuieli* service, int zi) {
    VectorDinamic rezultat = vector_dinamic_creeaza();
    const VectorDinamic* toate = repo_toate(service->repo);
    size_t n = vector_dinamic_dimensiune(toate);

    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(toate, i);
        if (c->zi == zi) {
            vector_dinamic_adauga(&rezultat, (void*)c);
        }
    }

    return rezultat;
}

VectorDinamic service_filtreaza_dupa_suma_minima(const ServiceCheltuieli* service, double suma_minima) {
    VectorDinamic rezultat = vector_dinamic_creeaza();
    const VectorDinamic* toate = repo_toate(service->repo);
    size_t n = vector_dinamic_dimensiune(toate);

    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(toate, i);
        if (c->suma >= suma_minima) {
            vector_dinamic_adauga(&rezultat, (void*)c);
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
                vector_dinamic_seteaza(cheltuieli, i, b);
                vector_dinamic_seteaza(cheltuieli, j, a);
            }
        }
    }
}
static void service_salveaza_snapshot(ServiceCheltuieli* service) {
    VectorDinamic* snapshot = malloc(sizeof(VectorDinamic));
    *snapshot = repo_copiaza_lista_cheltuieli(repo_toate(service->repo));
    vector_dinamic_adauga(&service->undo_list, snapshot);
}
void service_distruge(ServiceCheltuieli* service) {
    size_t n = vector_dinamic_dimensiune(&service->undo_list);
    for (size_t i = 0; i < n; i++) {
        VectorDinamic* snapshot = (VectorDinamic*)vector_dinamic_get(&service->undo_list, i);
        service_distruge_snapshot(snapshot);
    }
    vector_dinamic_distruge(&service->undo_list);
}
int service_undo(ServiceCheltuieli* service) {
    size_t n = vector_dinamic_dimensiune(&service->undo_list);
    if (n == 0) {
        return 1;
    }

    VectorDinamic* snapshot = (VectorDinamic*)vector_dinamic_get(&service->undo_list, n - 1);
    vector_dinamic_sterge(&service->undo_list, n - 1);
    repo_inlocuieste_toate(service->repo, *snapshot);
    free(snapshot);

    return 0;
}

static void service_distruge_snapshot(VectorDinamic* snapshot) {
    size_t n = vector_dinamic_dimensiune(snapshot);
    for (size_t i = 0; i < n; i++) {
        Cheltuiala* cheltuiala = (Cheltuiala*)vector_dinamic_get(snapshot, i);
        cheltuiala_distruge(cheltuiala);
    }
    vector_dinamic_distruge(snapshot);
    free(snapshot);
}
