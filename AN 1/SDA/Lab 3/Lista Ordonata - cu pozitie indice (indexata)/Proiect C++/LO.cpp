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
	if (i < 0 || i >= nrElem) {
        throw exception();
    }

	Nod* deSters;
	TElement elem;

	if (i == 0) {
		deSters = prim;
		prim = prim->urm;
	}
	else {
		Nod* current = prim;
		for (int j = 0; j < i - 1; j++) {
			current = current->urm;
		}

		deSters = current->urm;
		current->urm = deSters->urm;
	}

	elem = deSters->e;
	delete deSters;
	nrElem--;

	return elem;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	Nod* current = prim;
	int poz = 0;

	while (current != nullptr) {
		if (current->e == e) {
			return poz;
		}
		current = current->urm;
		poz++;
	}

	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	Nod* nou = new Nod;
	nou->e = e;
	nou->urm = nullptr;

	if (prim == nullptr || rel(e, prim->e)) {
		nou->urm = prim;
		prim = nou;
		nrElem++;
		return;
	}

	Nod* current = prim;
	while (current->urm != nullptr && !rel(e, current->urm->e)) {
		current = current->urm;
	}

	nou->urm = current->urm;
	current->urm = nou;
	nrElem++;
}

// returnare iterator
Iterator LO::iterator(){
	return Iterator(*this);
}


//destructor
LO::~LO() {
	while (prim != nullptr) {
		Nod* deSters = prim;
		prim = prim->urm;
		delete deSters;
	}
}
