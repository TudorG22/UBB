#pragma once


#include "LO.h"

class LO;


class Iterator{
	friend class LO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	//complexitate: BC = WC = Theta(1), initializeaza pozitia curenta
	Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lista;

	/* aici e reprezentarea  specifica a iteratorului */
	Nod* curent;


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		//complexitate: BC = WC = Theta(1), revine la inceput
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), trece la urmatoarea pozitie
		void urmator();

		//muta iteratorul in container cu k pozitii
		// arunca exceptie daca iteratorul nu e valid sau daca k e zero sau negativ
		//complexitate: WC = Theta(k), BC = Theta(1) trece la urmatoarea pozitie
		void avanseazaKPasi(int k);

		//verifica daca iteratorul e valid (indica un element al containerului)
		//complexitate: BC = WC = Theta(1), compara pozitia curenta
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), acceseaza elementul curent
		TElement element() const;
};


