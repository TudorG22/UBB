#include "validation/validator_domain.h"

int valideaza_domain_date(int zi, double suma, TipCheltuiala tip) {
    if (zi < 1 || zi > 31) return 0;
    if (suma < 0) return 0;
    if (tip < TIP_MANCARE || tip > TIP_ALTELE) return 0;
    return 1;
}

int valideaza_domain_cheltuiala(const Cheltuiala* cheltuiala) {
    return valideaza_domain_date(cheltuiala->zi, cheltuiala->suma, cheltuiala->tip);
}
