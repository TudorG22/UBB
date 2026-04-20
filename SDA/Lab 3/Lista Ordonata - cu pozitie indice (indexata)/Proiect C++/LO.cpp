#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	prim = nullptr;
	nrElem = 0;
	rel = r;
}

// returnare dimensiune
int LO::dim() const {
	return nrElem;
}

// verifica daca LO e vida
bool LO::vida() const {
	return (nrElem == 0);
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
    if (i < 0 || i >= nrElem) {
        throw exception();
    }

    Nod* current = prim;
    for (int j = 0; j < i; j++) {
        current = current->urm;
    }

    return current->e;
}


// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/* de adaugat */
	return -1;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/* de adaugat */
	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
}

// returnare iterator
Iterator LO::iterator(){
	return Iterator(*this);
}


//destructor
LO::~LO() {
	/* de adaugat */
}
