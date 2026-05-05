#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

Dictionar::Dictionar() {
	capacitate = 10;
	elems = new TElem[capacitate];
	urm = new int[capacitate];
	prec = new int[capacitate];

	prim = -1;
	ultim = -1;
	primLiber = 0;
	nrElem = 0;
	for (int i = 0; i < capacitate - 1; i++) {
		urm[i] = i + 1;
		prec[i] = -1;
	}
	urm[capacitate - 1] = -1;
	prec[capacitate - 1] = -1;
}

Dictionar::~Dictionar() {
	delete[] elems;
	delete[] urm;
	delete[] prec;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	for (int i = prim; i != -1; i = urm[i]) {
		if (elems[i].first == c) {
				TValoare veche = elems[i].second;
				elems[i].second = v;
				return veche;
		}
	}


	if (nrElem == capacitate) {
		int vecheCapacitate = capacitate;
		capacitate = capacitate * 2;
		TElem* nou_elems = new TElem[capacitate];
		int* nou_urm = new int[capacitate];
		int* nou_prec = new int[capacitate];
		
		for (int i = 0; i < vecheCapacitate; i++) {
			nou_urm[i] = urm[i];
			nou_prec[i] = prec[i];
			nou_elems[i] = elems[i];

		}

		for (int i = vecheCapacitate; i < capacitate - 1; i++) {
			nou_urm[i] = i + 1;
			nou_prec[i] = -1;
		}
		nou_urm[capacitate - 1] = -1;
		nou_prec[capacitate - 1] = -1;
		primLiber = vecheCapacitate;

		delete[] elems;
		delete[] urm;
		delete[] prec;

		elems = nou_elems;
		urm = nou_urm;
		prec = nou_prec;
	}

	int nou = primLiber;
	primLiber = urm[primLiber];
	
	elems[nou] = std::make_pair(c, v);
	urm[nou] = prim;
	prec[nou] = -1;

	if (prim != -1) {
		prec[prim] = nou;
	} 
	else {
		ultim = nou;
	}

	prim = nou;
	nrElem++;

	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	for (int i = prim; i != -1; i = urm[i]) {
		if (elems[i].first == c) {
			return elems[i].second;
		}
	}
	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	int i = prim;
	while (i != -1 && elems[i].first != c) {
		i = urm[i];
	}

	if (i == -1) {
		return NULL_TVALOARE;
	}

	TValoare valoareStearsa = elems[i].second;

	if (i == prim) {
		prim = urm[i];
		if (prim != -1) {
			prec[prim] = -1;
		}
	}
	else {
		urm[prec[i]] = urm[i];
	}

	if (i == ultim) {
		ultim = prec[i];
		if (ultim != -1) {
			urm[ultim] = -1;
		}
	}
	else {
		prec[urm[i]] = prec[i];
	}

	urm[i] = primLiber;
	primLiber = i;
	nrElem--;

	return valoareStearsa;
}


int Dictionar::dim() const {
	return nrElem;
}

bool Dictionar::vid() const{
	return (nrElem == 0);
}


IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}

int Dictionar::adaugaInexistente(Dictionar& d) {
	int adaugate = 0;
	for (int i = d.prim; i != -1; i = d.urm[i]) {
		TValoare rez = cauta(d.elems[i].first);
		if (rez == NULL_TVALOARE) {
			adauga(d.elems[i].first, d.elems[i].second);
			adaugate++;
		}
	}

	return adaugate;
}