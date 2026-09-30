#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <stack>

#include <exception>
using namespace std;

DO::DO(Relatie r) {
	radacina = nullptr;
	nrElemente = 0;
	rel = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	if (radacina == nullptr) {
		Nod* nou = new Nod;
		nou->elem = TElem(c, v);
		nou->stanga = nullptr;
		nou->dreapta = nullptr;
		radacina = nou;
		nrElemente++;
		return NULL_TVALOARE;
	}

	Nod* curent = radacina;
	Nod* parinte = nullptr;
	while (curent != nullptr) {
		if (curent->elem.first == c) {
			TValoare veche = curent->elem.second;
			curent->elem.second = v;
			return veche;
		}

		parinte = curent;
		if (rel(c, curent->elem.first)) {
			curent = curent->stanga;
		}
		else {
			curent = curent->dreapta;
		}
	}

	Nod* nou = new Nod;
	nou->elem = TElem(c, v);
	nou->stanga = nullptr;
	nou->dreapta = nullptr;

	if (rel(c, parinte->elem.first)) {
		parinte->stanga = nou;
	}
	else {
		parinte->dreapta = nou;
	}

	nrElemente++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	Nod* curent = radacina;
	while (curent != nullptr) {
		if (curent->elem.first == c) {
			return curent->elem.second;
		}

		if (rel(c, curent->elem.first)) {
			curent = curent->stanga;
		}
		else {
			curent = curent->dreapta;
		}
	}

	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	Nod* curent = radacina;
	Nod* parinte = nullptr;

	// cauta nodul care trebuie sters
	while (curent != nullptr && curent->elem.first != c) {
		parinte = curent;
		if (rel(c, curent->elem.first)) {
			curent = curent->stanga;
		}
		else {
			curent = curent->dreapta;
		}
	}

	if (curent == nullptr) {
		return NULL_TVALOARE;
	}

	TValoare valoareStearsa = curent->elem.second;

	// caz 1 ------ nodul are doi copii
	if (curent->stanga != nullptr && curent->dreapta != nullptr) {
		Nod* parinteSuccesor = curent;
		Nod* succesor = curent->dreapta;
		while (succesor->stanga != nullptr) {
			parinteSuccesor = succesor;
			succesor = succesor->stanga;
		}

		curent->elem = succesor->elem;
		curent = succesor;
		parinte = parinteSuccesor;
	}

	Nod* copil;
	// caz 2 ------ nodul are doar copil stang
	if (curent->stanga != nullptr) {
		copil = curent->stanga;
	}
	// caz 3 ------ nodul are copil drept sau nu are niciun copil
	else {
		copil = curent->dreapta;
	}

	// caz 4 ------ nodul sters este radacina
	if (parinte == nullptr) {
		radacina = copil;
	}
	// caz 5 ------ nodul sters este fiu stang
	else if (parinte->stanga == curent) {
		parinte->stanga = copil;
	}
	// caz 6 ------ nodul sters este fiu drept
	else {
		parinte->dreapta = copil;
	}

	delete curent;
	nrElemente--;
	return valoareStearsa;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return nrElemente;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	return nrElemente == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	stack<Nod*> stiva;
	if (radacina != nullptr) {
		stiva.push(radacina);
	}

	while (!stiva.empty()) {
		Nod* curent = stiva.top();
		stiva.pop();

		if (curent->stanga != nullptr) {
			stiva.push(curent->stanga);
		}
		if (curent->dreapta != nullptr) {
			stiva.push(curent->dreapta);
		}

		delete curent;
	}
}


void DO::inlocuiesteToate(Transformator t){
	stack<Nod*> stiva;
	if (radacina != nullptr) {
		stiva.push(radacina);
	}

	while (!stiva.empty()) {
		Nod* curent = stiva.top();
		stiva.pop();

		if (curent->stanga != nullptr) {
			stiva.push(curent->stanga);
		}
		if (curent->dreapta != nullptr) {
			stiva.push(curent->dreapta);
		}

		curent->elem.second = t(curent->elem.first, curent->elem.second);
	}
}