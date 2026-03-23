#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "domain/cheltuiala.h"
#include "repository/repo_cheltuieli.h"
#include "service/service_cheltuieli.h"
#include "utils/vector_dinamic.h"
#include "validation/validator_domain.h"
#include "validation/validator_repo.h"
#include "validation/validator_service.h"

static void test_domain(void) {
    Cheltuiala c = cheltuiala_creeaza(10, 50.5, TIP_TRANSPORT);
    assert(cheltuiala_get_zi(&c) == 10);
    assert(cheltuiala_get_suma(&c) == 50.5);
    assert(cheltuiala_get_tip(&c) == TIP_TRANSPORT);

    cheltuiala_set_zi(&c, 20);
    cheltuiala_set_suma(&c, 99.9);
    cheltuiala_set_tip(&c, TIP_ALTELE);

    assert(cheltuiala_get_zi(&c) == 20);
    assert(cheltuiala_get_suma(&c) == 99.9);
    assert(cheltuiala_get_tip(&c) == TIP_ALTELE);
    assert(strcmp(tip_cheltuiala_la_text(TIP_MANCARE), "mancare") == 0);
    assert(strcmp(tip_cheltuiala_la_text(TIP_TRANSPORT), "transport") == 0);
    assert(strcmp(tip_cheltuiala_la_text(TIP_TELEFON_INTERNET), "telefon&internet") == 0);
    assert(strcmp(tip_cheltuiala_la_text(TIP_IMBRACAMINTE), "imbracaminte") == 0);
    assert(strcmp(tip_cheltuiala_la_text(TIP_ALTELE), "altele") == 0);
    assert(strcmp(tip_cheltuiala_la_text((TipCheltuiala)999), "necunoscut") == 0);
}

static void test_vector(void) {
    VectorDinamic v = vector_dinamic_creeaza(sizeof(int));
    int a = 7, b = 9, c = 11;

    vector_dinamic_adauga(&v, &a);
    vector_dinamic_adauga(&v, &b);
    assert(vector_dinamic_dimensiune(&v) == 2);
    assert(*(int*)vector_dinamic_get(&v, 0) == 7);
    assert(*(const int*)vector_dinamic_get_const(&v, 1) == 9);

    vector_dinamic_seteaza(&v, 1, &c);
    assert(*(int*)vector_dinamic_get(&v, 1) == 11);

    vector_dinamic_sterge(&v, 0);
    assert(vector_dinamic_dimensiune(&v) == 1);
    assert(*(int*)vector_dinamic_get(&v, 0) == 11);

    vector_dinamic_distruge(&v);
}

static void test_repo(void) {
    RepoCheltuieli repo = repo_creaza();
    Cheltuiala c1 = cheltuiala_creeaza(1, 10, TIP_MANCARE);
    Cheltuiala c2 = cheltuiala_creeaza(2, 20, TIP_TRANSPORT);
    Cheltuiala c3 = cheltuiala_creeaza(3, 30, TIP_ALTELE);

    repo_adauga(&repo, c1);
    repo_adauga(&repo, c2);
    assert(repo_dimensiune(&repo) == 2);
    assert(repo_get(&repo, 0).zi == 1);

    repo_modifica(&repo, 1, c3);
    assert(repo_get(&repo, 1).zi == 3);

    assert(repo_toate(&repo) != NULL);
    repo_sterge(&repo, 0);
    assert(repo_dimensiune(&repo) == 1);
    assert(repo_get(&repo, 0).zi == 3);

    repo_distruge(&repo);
}

static void test_service(void) {
    RepoCheltuieli repo = repo_creaza();
    ServiceCheltuieli srv = service_creeaza(&repo);

    assert(service_numar_cheltuieli(&srv) == 0);
    assert(service_lista(&srv) != NULL);

    service_adauga_cheltuiala(&srv, 10, 100, TIP_MANCARE);
    service_adauga_cheltuiala(&srv, 5, 40, TIP_TRANSPORT);
    service_adauga_cheltuiala(&srv, 8, 70, TIP_ALTELE);
    assert(service_numar_cheltuieli(&srv) == 3);

    service_modifica_cheltuiala(&srv, 1, 6, 45, TIP_TRANSPORT);
    assert(repo_get(&repo, 1).zi == 6);

    VectorDinamic f_tip = service_filtreaza_dupa_tip(&srv, TIP_TRANSPORT);
    VectorDinamic f_zi = service_filtreaza_dupa_zi(&srv, 10);
    VectorDinamic f_suma = service_filtreaza_dupa_suma_minima(&srv, 70);
    assert(vector_dinamic_dimensiune(&f_tip) == 1);
    assert(vector_dinamic_dimensiune(&f_zi) == 1);
    assert(vector_dinamic_dimensiune(&f_suma) == 2);

    VectorDinamic sort_suma = service_filtreaza_dupa_suma_minima(&srv, 0);
    service_sorteaza(&sort_suma, 1, SERVICE_SORT_CHEIE_SUMA);
    assert(((Cheltuiala*)vector_dinamic_get(&sort_suma, 0))->suma <=
           ((Cheltuiala*)vector_dinamic_get(&sort_suma, 1))->suma);
    service_sorteaza(&sort_suma, 0, SERVICE_SORT_CHEIE_SUMA);
    assert(((Cheltuiala*)vector_dinamic_get(&sort_suma, 0))->suma >=
           ((Cheltuiala*)vector_dinamic_get(&sort_suma, 1))->suma);

    VectorDinamic sort_tip = service_filtreaza_dupa_suma_minima(&srv, 0);
    service_sorteaza(&sort_tip, 1, SERVICE_SORT_CHEIE_TIP);
    assert(((Cheltuiala*)vector_dinamic_get(&sort_tip, 0))->tip <=
           ((Cheltuiala*)vector_dinamic_get(&sort_tip, 1))->tip);
    service_sorteaza(&sort_tip, 0, SERVICE_SORT_CHEIE_TIP);
    assert(((Cheltuiala*)vector_dinamic_get(&sort_tip, 0))->tip >=
           ((Cheltuiala*)vector_dinamic_get(&sort_tip, 1))->tip);

    VectorDinamic sort_invalid = service_filtreaza_dupa_suma_minima(&srv, 0);
    Cheltuiala inainte = *(Cheltuiala*)vector_dinamic_get(&sort_invalid, 0);
    service_sorteaza(&sort_invalid, 1, (ServiceSortCheie)999);
    Cheltuiala dupa = *(Cheltuiala*)vector_dinamic_get(&sort_invalid, 0);
    assert(dupa.zi == inainte.zi);
    assert(dupa.suma == inainte.suma);
    assert(dupa.tip == inainte.tip);

    service_sterge_cheltuiala(&srv, 2);
    assert(service_numar_cheltuieli(&srv) == 2);

    vector_dinamic_distruge(&f_tip);
    vector_dinamic_distruge(&f_zi);
    vector_dinamic_distruge(&f_suma);
    vector_dinamic_distruge(&sort_suma);
    vector_dinamic_distruge(&sort_tip);
    vector_dinamic_distruge(&sort_invalid);
    repo_distruge(&repo);
}

static void test_validation(void) {
    Cheltuiala c = cheltuiala_creeaza(1, 1, TIP_MANCARE);
    RepoCheltuieli repo = repo_creaza();
    ServiceCheltuieli srv = service_creeaza(&repo);
    ServiceCheltuieli srv_invalid = {NULL};

    assert(valideaza_domain_date(1, 0, TIP_ALTELE) == 1);
    assert(valideaza_domain_date(32, 0, TIP_ALTELE) == 0);
    assert(valideaza_domain_cheltuiala(&c) == 1);

    assert(valideaza_repo(&repo) == 1);
    repo_adauga(&repo, c);
    assert(valideaza_repo_index(&repo, 0) == 1);
    assert(valideaza_repo_index(&repo, 1) == 0);

    assert(valideaza_service(&srv) == 1);
    assert(valideaza_service(&srv_invalid) == 0);
    assert(valideaza_service_date_cheltuiala(1, 10, TIP_MANCARE) == 1);
    assert(valideaza_service_date_cheltuiala(0, 10, TIP_MANCARE) == 0);

    repo_distruge(&repo);
}

void ruleaza_toate_testele(void) {
    test_domain();
    test_vector();
    test_repo();
    test_service();
    test_validation();
    printf("Toate testele au trecut.\n");
}
