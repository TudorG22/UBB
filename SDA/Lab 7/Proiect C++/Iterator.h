#pragma once

#include "DO.h"
#include <vector>

class Iterator{
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	// complexitate: BC = WC = O(n), memoreaza elementele in ordine
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	std::vector<TElem> elemente;
	int pozitie;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		// complexitate: BC = WC = Theta(1)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		// complexitate: BC = WC = Theta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		// complexitate: BC = WC = Theta(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		// complexitate: BC = WC = Theta(1)
		TElem element() const;
};
