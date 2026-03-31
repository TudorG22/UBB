#pragma once
#include <utility>

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
		
		std::pair<TElem,int>* date;
		int capacitate;
		int dimensiune;
		int dimensiune_real;

		

public:
		//constructorul implicit
		//complexitate: BC = WC = Theta(1), initializeaza campurile
		Colectie();

		int bin_search(TElem e) ;
		bool bin_search_bool(TElem e) ;

		//adauga un element in colectie
		//complexitate: BC = Theta(1), WC = O(n), parcurgere liniara
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		//complexitate: BC = Theta(1), WC = O(n), parcurgere liniara
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		//complexitate: BC = Theta(1), WC = O(n), parcurgere liniara
		bool cauta(TElem elem) ;

		//returneaza numar de aparitii ale unui element in colectie
		//complexitate: BC = Theta(1), WC = O(n), parcurgere liniara
		int nrAparitii(TElem elem) ;

		//intoarce numarul de elemente din colectie;
		//complexitate: BC = WC = Theta(1), returneaza un camp
		int dim() const;

		//verifica daca colectia e vida;
		//complexitate: BC = WC = Theta(1), verifica un camp
		bool vida() const;

		//returneaza un iterator pe colectie
		//complexitate: BC = WC = Theta(1), construieste iteratorul
		IteratorColectie iterator() const;

		// destructorul colectiei
		//complexitate: BC = WC = Theta(1), elibereaza memoria
		~Colectie();


};
