#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
    private:
	struct Nod {
		TElem elem;
		Nod* stanga;
		Nod* dreapta;
	};

	Nod* radacina;
	int nrElemente;
	Relatie rel;

    public:

	// constructorul implicit al dictionarului
	// complexitate: BC = WC = Theta(1), initializeaza campurile
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	// complexitate: BC = Theta(1), WC = O(n), unde n este numarul de noduri
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	// complexitate: BC = Theta(1), WC = O(n), unde n este numarul de noduri
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	// complexitate: BC = Theta(1), WC = O(n), unde n este numarul de noduri
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	// complexitate: BC = WC = Theta(1), returneaza un camp
	int dim() const;

	//verifica daca dictionarul e vid
	// complexitate: BC = WC = Theta(1), verifica un camp
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	// complexitate: BC = WC = O(n), construieste iteratorul prin parcurgere inordine
	Iterator iterator() const;


	// destructorul dictionarului
	// complexitate: BC = WC = Theta(n), elibereaza toate nodurile
	~DO();

};
