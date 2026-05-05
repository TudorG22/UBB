#pragma once


#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;

class Dictionar {
	friend class IteratorDictionar;

	private:
		TElem* elems;
		int* urm;
		int* prec;
		int prim;
		int ultim;
		int primLiber;
		int capacitate;
		int nrElem;

	public:

	// constructorul implicit al dictionarului
	//complexitate: BC = WC = Theta(1), initializeaza campurile si lista spatiului liber
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	//complexitate: BC = Theta(1), WC = O(n), cautare liniara; redimensionarea are cost amortizat
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	//complexitate: BC = Theta(1), WC = O(n), parcurgere liniara
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	//complexitate: BC = Theta(1), WC = O(n), cautare liniara, stergerea efectiva este Theta(1)
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	//complexitate: BC = WC = Theta(1), returneaza un camp
	int dim() const;

	//verifica daca dictionarul e vid 
	//complexitate: BC = WC = Theta(1), verifica un camp
	bool vid() const;

	// se returneaza iterator pe dictionar
	//complexitate: BC = WC = Theta(1), construieste iteratorul
	IteratorDictionar iterator() const;

	//la lab
	int adaugaInexistente(Dictionar& d);

	// destructorul dictionarului	
	//complexitate: BC = WC = Theta(capacitate), elibereaza tablourile
	~Dictionar();

};


