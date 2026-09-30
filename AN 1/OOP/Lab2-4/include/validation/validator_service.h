#ifndef VALIDATOR_SERVICE_H
#define VALIDATOR_SERVICE_H

#include "service/service_cheltuieli.h"

/* Valideaza service-ul
Input: service
Output: 1 valid / 0 invalid
Pre conditii: -
Post conditii: -
*/
int valideaza_service(const ServiceCheltuieli* service);

/* Valideaza datele folosite de service pentru cheltuiala
Input: zi, suma, tip
Output: 1 valid / 0 invalid
Pre conditii: -
Post conditii: -
*/
int valideaza_service_date_cheltuiala(int zi, double suma, TipCheltuiala tip);

#endif
