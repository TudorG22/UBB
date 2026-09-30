#include "ui/interfata_consola.h"
#include "validation/validator_domain.h"

#include <stdio.h>

void curata_buffer_intrare(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

int citeste_int(const char* mesaj, int* valoare) {
    printf("%s", mesaj);
    if (scanf("%d", valoare) != 1) {
        curata_buffer_intrare();
        return 0;
    }
    return 1;
}

int citeste_double(const char* mesaj, double* valoare) {
    printf("%s", mesaj);
    if (scanf("%lf", valoare) != 1) {
        curata_buffer_intrare();
        return 0;
    }
    return 1;
}

int citeste_size_t(const char* mesaj, size_t* valoare) {
    printf("%s", mesaj);
    if (scanf("%zu", valoare) != 1) {
        curata_buffer_intrare();
        return 0;
    }
    return 1;
}

void afiseaza_meniu(void) {
    printf("\n=== Buget Familie ===\n");
    printf("1. Adauga cheltuiala\n");
    printf("2. Modifica cheltuiala\n");
    printf("3. Sterge cheltuiala\n");
    printf("4. Listeaza filtrat\n");
    printf("5. Listeaza sortat\n");
    printf("0. Iesire\n");
}

void afiseaza_tipuri(void) {
    printf("Tipuri: 0-mancare, 1-transport, 2-telefon&internet, 3-imbracaminte, 4-altele\n");
}

int index_valid(const ServiceCheltuieli* service, size_t index) {
    return index < service_numar_cheltuieli(service);
}

void afiseaza_lista(const VectorDinamic* lista) {
    size_t n = vector_dinamic_dimensiune(lista);
    if (n == 0) {
        printf("Nu exista cheltuieli.\n");
        return;
    }

    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(lista, i);
        printf("%zu) zi=%d, suma=%.2f, tip=%s\n", i, c->zi, c->suma, tip_cheltuiala_la_text(c->tip));
    }
}

VectorDinamic copiaza_lista(const VectorDinamic* lista) {
    VectorDinamic copie = vector_dinamic_creeaza(sizeof(Cheltuiala));
    size_t n = vector_dinamic_dimensiune(lista);
    for (size_t i = 0; i < n; i++) {
        const Cheltuiala* c = (const Cheltuiala*)vector_dinamic_get_const(lista, i);
        vector_dinamic_adauga(&copie, c);
    }
    return copie;
}

void ui_adauga(ServiceCheltuieli* service) {
    int zi;
    double suma;
    int tip_int;

    if (!citeste_int("Zi: ", &zi)) {
        printf("Input invalid.\n");
        return;
    }
    if (!citeste_double("Suma: ", &suma)) {
        printf("Input invalid.\n");
        return;
    }
    afiseaza_tipuri();
    if (!citeste_int("Tip: ", &tip_int)) {
        printf("Input invalid.\n");
        return;
    }

    if (!valideaza_domain_date(zi, suma, (TipCheltuiala)tip_int)) {
        printf("Date invalide.\n");
        return;
    }

    service_adauga_cheltuiala(service, zi, suma, (TipCheltuiala)tip_int);
    printf("Adaugata.\n");
}

void ui_modifica(ServiceCheltuieli* service) {
    size_t index;
    int zi;
    double suma;
    int tip_int;

    afiseaza_lista(service_lista(service));
    if (!citeste_size_t("Index: ", &index)) {
        printf("Input invalid.\n");
        return;
    }
    if (!citeste_int("Zi noua: ", &zi)) {
        printf("Input invalid.\n");
        return;
    }
    if (!citeste_double("Suma noua: ", &suma)) {
        printf("Input invalid.\n");
        return;
    }
    afiseaza_tipuri();
    if (!citeste_int("Tip nou: ", &tip_int)) {
        printf("Input invalid.\n");
        return;
    }

    if (!index_valid(service, index)) {
        printf("Index invalid.\n");
        return;
    }

    if (!valideaza_domain_date(zi, suma, (TipCheltuiala)tip_int)) {
        printf("Date invalide.\n");
        return;
    }

    service_modifica_cheltuiala(service, index, zi, suma, (TipCheltuiala)tip_int);
    printf("Modificata.\n");
}

void ui_sterge(ServiceCheltuieli* service) {
    size_t index;

    afiseaza_lista(service_lista(service));
    if (!citeste_size_t("Index: ", &index)) {
        printf("Input invalid.\n");
        return;
    }

    if (!index_valid(service, index)) {
        printf("Index invalid.\n");
        return;
    }

    service_sterge_cheltuiala(service, index);
    printf("Stearsa.\n");
}

void ui_filtrare(ServiceCheltuieli* service) {
    int opt;
    VectorDinamic rezultat;

    printf("Filtrare: 1-tip, 2-zi, 3-suma minima\n");
    if (!citeste_int("Optiune: ", &opt)) {
        printf("Input invalid.\n");
        return;
    }

    if (opt == 1) {
        int tip_int;
        afiseaza_tipuri();
        if (!citeste_int("Tip: ", &tip_int)) {
            printf("Input invalid.\n");
            return;
        }
        if (tip_int < TIP_MANCARE || tip_int > TIP_ALTELE) {
            printf("Tip invalid.\n");
            return;
        }
        rezultat = service_filtreaza_dupa_tip(service, (TipCheltuiala)tip_int);
    } else if (opt == 2) {
        int zi;
        if (!citeste_int("Zi: ", &zi)) {
            printf("Input invalid.\n");
            return;
        }
        if (zi < 1 || zi > 31) {
            printf("Zi invalida.\n");
            return;
        }
        rezultat = service_filtreaza_dupa_zi(service, zi);
    } else if (opt == 3) {
        double suma_minima;
        if (!citeste_double("Suma minima: ", &suma_minima)) {
            printf("Input invalid.\n");
            return;
        }
        if (suma_minima < 0) {
            printf("Suma invalida.\n");
            return;
        }
        rezultat = service_filtreaza_dupa_suma_minima(service, suma_minima);
    } else {
        printf("Optiune invalida.\n");
        return;
    }

    afiseaza_lista(&rezultat);
    vector_dinamic_distruge(&rezultat);
}

void ui_sortare(ServiceCheltuieli* service) {
    int criteriu;
    int ordine;
    int crescator;
    VectorDinamic lista_sortata = copiaza_lista(service_lista(service));

    printf("Sortare: 1-suma, 2-tip\n");
    if (!citeste_int("Criteriu: ", &criteriu)) {
        printf("Input invalid.\n");
        vector_dinamic_distruge(&lista_sortata);
        return;
    }
    printf("Ordine: 1-crescator, 2-descrescator\n");
    if (!citeste_int("Ordine: ", &ordine)) {
        printf("Input invalid.\n");
        vector_dinamic_distruge(&lista_sortata);
        return;
    }

    if (ordine != 1 && ordine != 2) {
        printf("Ordine invalida.\n");
        vector_dinamic_distruge(&lista_sortata);
        return;
    }

    crescator = (ordine == 1);

    if (criteriu != SERVICE_SORT_CHEIE_SUMA && criteriu != SERVICE_SORT_CHEIE_TIP) {
        printf("Criteriu invalid.\n");
        vector_dinamic_distruge(&lista_sortata);
        return;
    }

    service_sorteaza(&lista_sortata, crescator, (ServiceSortCheie)criteriu);

    afiseaza_lista(&lista_sortata);
    vector_dinamic_distruge(&lista_sortata);
}

void ruleaza_interfata(ServiceCheltuieli* service) {
    int comanda = -1;

    while (comanda != 0) {
        afiseaza_meniu();
        if (!citeste_int("Comanda: ", &comanda)) {
            printf("Input invalid.\n");
            continue;
        }

        if (comanda == 1) ui_adauga(service);
        else if (comanda == 2) ui_modifica(service);
        else if (comanda == 3) ui_sterge(service);
        else if (comanda == 4) ui_filtrare(service);
        else if (comanda == 5) ui_sortare(service);
        else if (comanda == 0) printf("La revedere!\n");
        else printf("Comanda invalida.\n");
    }
}
