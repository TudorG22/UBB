#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

struct Celula {
	TElem elem;
	int frecventa;
	int stare;
};

class Colectie
{
	friend class IteratorColectie;

private:
	Celula* tabela;
	int capacitate;
	int nrElemente;
	int nrDistincte;

	int dispersie(TElem e) const;
	int pozitie(TElem e, int i) const;
	void redimensionareAdauga();
	void redimensionareSterge();
public:
		//constructorul implicit
		//complexitate: BC = WC = Theta(m), initializeaza tabela
		Colectie();

		//adauga un element in colectie
		//complexitate: BC = Theta(1), WC = O(m), in medie Theta(1); redimensionarea are cost amortizat
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		//complexitate: BC = Theta(1), WC = O(m), in medie Theta(1)
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		//complexitate: BC = Theta(1), WC = O(m), in medie Theta(1)
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		//complexitate: BC = Theta(1), WC = O(m), in medie Theta(1)
		int nrAparitii(TElem elem) const;


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
