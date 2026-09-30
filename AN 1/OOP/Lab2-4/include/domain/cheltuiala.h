#ifndef CHELTUIALA_H
#define CHELTUIALA_H

typedef enum {
    TIP_MANCARE,
    TIP_TRANSPORT,
    TIP_TELEFON_INTERNET,
    TIP_IMBRACAMINTE,
    TIP_ALTELE
} TipCheltuiala;

typedef struct {
    int zi;
    double suma;
    TipCheltuiala tip;
} Cheltuiala;

/* Creeaza o cheltuiala
Input: zi, suma, tip
Output: cheltuiala noua
Pre conditii: zi si suma valide, tip valid
Post conditii: cheltuiala initializata
*/
Cheltuiala cheltuiala_creeaza(int zi, double suma, TipCheltuiala tip);

/* Returneaza ziua cheltuielii
Input: cheltuiala
Output: zi
Pre conditii: cheltuiala initializata
Post conditii: -
*/
int cheltuiala_get_zi(const Cheltuiala* c);

/* Returneaza suma cheltuielii
Input: cheltuiala
Output: suma
Pre conditii: cheltuiala initializata
Post conditii: -
*/
double cheltuiala_get_suma(const Cheltuiala* c);

/* Returneaza tipul cheltuielii
Input: cheltuiala
Output: tip
Pre conditii: cheltuiala initializata
Post conditii: -
*/
TipCheltuiala cheltuiala_get_tip(const Cheltuiala* c);

/* Seteaza ziua cheltuielii
Input: cheltuiala, zi
Output: -
Pre conditii: cheltuiala initializata
Post conditii: zi actualizata
*/
void cheltuiala_set_zi(Cheltuiala* c, int zi);

/* Seteaza suma cheltuielii
Input: cheltuiala, suma
Output: -
Pre conditii: cheltuiala initializata
Post conditii: suma actualizata
*/
void cheltuiala_set_suma(Cheltuiala* c, double suma);

/* Seteaza tipul cheltuielii
Input: cheltuiala, tip
Output: -
Pre conditii: cheltuiala initializata, tip valid
Post conditii: tip actualizat
*/
void cheltuiala_set_tip(Cheltuiala* c, TipCheltuiala tip);

/* Returneaza textul asociat tipului
Input: tip
Output: text tip
Pre conditii: -
Post conditii: -
*/
const char* tip_cheltuiala_la_text(TipCheltuiala tip);

#endif
