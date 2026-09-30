#ifndef VALIDATOR_DOMAIN_H
#define VALIDATOR_DOMAIN_H

#include "domain/cheltuiala.h"

/* Valideaza o cheltuiala
Input: cheltuiala
Output: 1 valid / 0 invalid
Pre conditii: pointer valid
Post conditii: -
*/
int valideaza_domain_cheltuiala(const Cheltuiala* cheltuiala);

/* Valideaza datele unei cheltuieli
Input: zi, suma, tip
Output: 1 valid / 0 invalid
Pre conditii: -
Post conditii: -
*/
int valideaza_domain_date(int zi, double suma, TipCheltuiala tip);

#endif
