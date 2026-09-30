#pragma once
#include "Dictionar.h"

class IteratorDictionar
{
	friend class Dictionar;
private:

    	//constructorul primeste o referinta catre Container
    	//iteratorul va referi primul element din container
	//complexitate: BC = WC = Theta(1), initializeaza campurile iteratorului
	IteratorDictionar(const Dictionar& d);

	//contine o referinta catre containerul pe care il itereaza
	const Dictionar& dict;
	int curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		//complexitate: BC = WC = Theta(1), muta curent pe prim
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), avanseaza la urmatorul nod
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		//complexitate: BC = WC = Theta(1), verifica daca pozitia curenta exista
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), returneaza elementul curent
		TElem element() const;
};
