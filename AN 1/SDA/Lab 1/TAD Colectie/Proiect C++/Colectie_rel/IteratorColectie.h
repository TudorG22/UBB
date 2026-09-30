#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;

private:
    //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	//complexitate: BC = WC = Theta(1), initializeaza pozitia curenta
    IteratorColectie(const Colectie& c);

    //contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	/* aici e reprezentarea  spcifica a iteratorului*/
	int curent = 0;
	int frec_curent = 0;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		//complexitate: BC = WC = Theta(1), revine la inceput
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), trece la urmatoarea pozitie/aparitie
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		//complexitate: BC = WC = Theta(1), compara pozitia curenta
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		//complexitate: BC = WC = Theta(1), acceseaza elementul curent
		TElem element() const;
};

