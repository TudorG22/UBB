#include "validation/validator_service.h"
#include "validation/validator_domain.h"

int valideaza_service(const ServiceCheltuieli* service) {
    return service->repo != NULL;
}

int valideaza_service_date_cheltuiala(int zi, double suma, TipCheltuiala tip) {
    return valideaza_domain_date(zi, suma, tip);
}
