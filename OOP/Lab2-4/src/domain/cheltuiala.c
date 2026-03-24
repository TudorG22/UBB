#include "domain/cheltuiala.h"

#include <stdlib.h>

Cheltuiala cheltuiala_creeaza(int zi, double suma, TipCheltuiala tip) {
    Cheltuiala c;
    c.zi = zi;
    c.suma = suma;
    c.tip = tip;
    return c;
}

int cheltuiala_get_zi(const Cheltuiala* c) { return c->zi; }
double cheltuiala_get_suma(const Cheltuiala* c) { return c->suma; }
TipCheltuiala cheltuiala_get_tip(const Cheltuiala* c) { return c->tip; }
Cheltuiala* cheltuiala_copiaza(const Cheltuiala* c) {
    Cheltuiala* copie = malloc(sizeof(Cheltuiala));
    *copie = *c;
    return copie;
}

void cheltuiala_distruge(Cheltuiala* c) {
    free(c);
}


void cheltuiala_set_zi(Cheltuiala* c, int zi) { c->zi = zi; }
void cheltuiala_set_suma(Cheltuiala* c, double suma) { c->suma = suma; }
void cheltuiala_set_tip(Cheltuiala* c, TipCheltuiala tip) { c->tip = tip; }

const char* tip_cheltuiala_la_text(TipCheltuiala tip) {
    switch (tip) {
        case TIP_MANCARE: return "mancare";
        case TIP_TRANSPORT: return "transport";
        case TIP_TELEFON_INTERNET: return "telefon&internet";
        case TIP_IMBRACAMINTE: return "imbracaminte";
        case TIP_ALTELE: return "altele";
        default: return "necunoscut";
    }
}
