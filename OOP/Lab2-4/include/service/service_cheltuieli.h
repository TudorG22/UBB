#ifndef SERVICE_CHELTUIELI_H
#define SERVICE_CHELTUIELI_H

#include <stddef.h>

#include "repository/repo_cheltuieli.h"

typedef struct {
    RepoCheltuieli* repo;
    VectorDinamic undo_list;
} ServiceCheltuieli;

typedef enum {
    SERVICE_SORT_CHEIE_SUMA = 1,
    SERVICE_SORT_CHEIE_TIP = 2
} ServiceSortCheie;
/**
 * Distruge istoricul de undo al service-ului
 * Input: service
 * Output: -
 * Pre conditii: service initializat
 * Post conditii: toate snapshot-urile din undo sunt eliberate
 **/
void service_distruge(ServiceCheltuieli* service);
/**
 * Reface ultima stare salvata a listei de cheltuieli
 * Input: service
 * Output: 0 daca undo s-a realizat, 1 daca nu exista operatii de undo
 * Pre conditii: service initializat
 * Post conditii: repo-ul revine la ultima stare salvata, daca aceasta exista
 **/
int service_undo(ServiceCheltuieli* service);
/* Creeaza service-ul
Input: repo
Output: service nou
Pre conditii: repo initializat
Post conditii: service legat la repo
*/
ServiceCheltuieli service_creeaza(RepoCheltuieli* repo);

/* Returneaza numarul de cheltuieli din service
Input: service
Output: numar cheltuieli
Pre conditii: service initializat
Post conditii: -
*/
size_t service_numar_cheltuieli(const ServiceCheltuieli* service);

/* Returneaza lista de cheltuieli din service
Input: service
Output: pointer la vector
Pre conditii: service initializat
Post conditii: -
*/
const VectorDinamic* service_lista(const ServiceCheltuieli* service);

/* Adauga o cheltuiala prin service
Input: service, zi, suma, tip
Output: cod stare (0 succes)
Pre conditii: service initializat, date valide
Post conditii: cheltuiala adaugata
*/
int service_adauga_cheltuiala(ServiceCheltuieli* service, int zi, double suma, TipCheltuiala tip);

/* Modifica o cheltuiala prin service
Input: service, index, zi, suma, tip
Output: cod stare (0 succes)
Pre conditii: service initializat, index valid, date valide
Post conditii: cheltuiala de pe index actualizata
*/
int service_modifica_cheltuiala(ServiceCheltuieli* service, size_t index, int zi, double suma, TipCheltuiala tip);

/* Sterge o cheltuiala prin service
Input: service, index
Output: cod stare (0 succes)
Pre conditii: service initializat, index valid
Post conditii: cheltuiala eliminata
*/
int service_sterge_cheltuiala(ServiceCheltuieli* service, size_t index);

/* Filtreaza cheltuielile dupa tip
Input: service, tip
Output: vector cu rezultate
Pre conditii: service initializat
Post conditii: vector nou alocat cu elementele filtrate
*/
VectorDinamic service_filtreaza_dupa_tip(const ServiceCheltuieli* service, TipCheltuiala tip);

/* Filtreaza cheltuielile dupa zi
Input: service, zi
Output: vector cu rezultate
Pre conditii: service initializat
Post conditii: vector nou alocat cu elementele filtrate
*/
VectorDinamic service_filtreaza_dupa_zi(const ServiceCheltuieli* service, int zi);

/* Filtreaza cheltuielile dupa suma minima
Input: service, suma minima
Output: vector cu rezultate
Pre conditii: service initializat
Post conditii: vector nou alocat cu elementele filtrate
*/
VectorDinamic service_filtreaza_dupa_suma_minima(const ServiceCheltuieli* service, double suma_minima);

/* Sorteaza lista de cheltuieli dupa o cheie
Input: vector cheltuieli, ordine, cheie
Output: -
Pre conditii: vector initializat, cheie valida
Post conditii: vectorul este ordonat in-place
*/
void service_sorteaza(VectorDinamic* cheltuieli, int crescator, ServiceSortCheie cheie);
#endif
