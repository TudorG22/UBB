#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>

using namespace std;

static const int LIBER = 0;
static const int OCUPAT = 1;
static const int STERS = 2;
static const int CAPACITATE_MINIMA = 11;

static bool estePrim(int x) {
	if (x < 2) {
		return false;
	}
	if (x % 2 == 0) {
		return x == 2;
	}
	for (int d = 3; d * d <= x; d += 2) {
		if (x % d == 0) {
			return false;
		}
	}
	return true;
}

static int urmatorPrim(int x) {
	if (x <= 2) {
		return 2;
	}
	if (x % 2 == 0) {
		x++;
	}
	while (!estePrim(x)) {
		x += 2;
	}
	return x;
}

int Colectie::dispersie(TElem e) const {
	int rez = e % capacitate;
	if (rez < 0) {
		rez += capacitate;
	}
	return rez;
}

int Colectie::pozitie(TElem e, int i) const {
	return (dispersie(e) + i * i) % capacitate;
}

void Colectie::redimensionareAdauga() {
	int capacitateVeche = capacitate;
	Celula* tabelaVeche = tabela;

	capacitate = urmatorPrim(capacitate * 2);
	tabela = new Celula[capacitate];
	for (int i = 0; i < capacitate; i++) {
		tabela[i].elem = NULL_TELEM;
		tabela[i].frecventa = 0;
		tabela[i].stare = LIBER;
	}

	int vechiDistincte = nrDistincte;
	nrDistincte = 0;

	for (int i = 0; i < capacitateVeche; i++) {
		if (tabelaVeche[i].stare == OCUPAT) {
			int k = 0;
			int j = pozitie(tabelaVeche[i].elem, k);
			while (tabela[j].stare == OCUPAT) {
				k++;
				j = pozitie(tabelaVeche[i].elem, k);
			}
			tabela[j].elem = tabelaVeche[i].elem;
			tabela[j].frecventa = tabelaVeche[i].frecventa;
			tabela[j].stare = OCUPAT;
			nrDistincte++;
		}
	}

	delete[] tabelaVeche;
	nrDistincte = vechiDistincte;
}

void Colectie::redimensionareSterge() {
	if (capacitate == CAPACITATE_MINIMA) {
		return;
	}

	int capacitateVeche = capacitate;
	Celula* tabelaVeche = tabela;

	capacitate = urmatorPrim(capacitate / 2);
	if (capacitate < CAPACITATE_MINIMA) {
		capacitate = CAPACITATE_MINIMA;
	}

	tabela = new Celula[capacitate];
	for (int i = 0; i < capacitate; i++) {
		tabela[i].elem = NULL_TELEM;
		tabela[i].frecventa = 0;
		tabela[i].stare = LIBER;
	}

	int vechiDistincte = nrDistincte;
	nrDistincte = 0;

	for (int i = 0; i < capacitateVeche; i++) {
		if (tabelaVeche[i].stare == OCUPAT) {
			int k = 0;
			int j = pozitie(tabelaVeche[i].elem, k);
			while (tabela[j].stare == OCUPAT) {
				k++;
				j = pozitie(tabelaVeche[i].elem, k);
			}
			tabela[j].elem = tabelaVeche[i].elem;
			tabela[j].frecventa = tabelaVeche[i].frecventa;
			tabela[j].stare = OCUPAT;
			nrDistincte++;
		}
	}

	delete[] tabelaVeche;
	nrDistincte = vechiDistincte;
}

Colectie::Colectie() {
	capacitate = CAPACITATE_MINIMA;
	nrElemente = 0;
	nrDistincte = 0;
	tabela = new Celula[capacitate];
	for (int i = 0; i < capacitate; i++) {
		tabela[i].elem = NULL_TELEM;
		tabela[i].frecventa = 0;
		tabela[i].stare = LIBER;
	}
}


void Colectie::adauga(TElem elem) {
	if ((nrDistincte + 1) * 2 >= capacitate) {
		redimensionareAdauga();
	}

	int primaStearsa = -1;
	for (int i = 0; i < capacitate; i++) {
		int j = pozitie(elem, i);

		if (tabela[j].stare == OCUPAT && tabela[j].elem == elem) {
			tabela[j].frecventa++;
			nrElemente++;
			return;
		}

		if (tabela[j].stare == STERS && primaStearsa == -1) {
			primaStearsa = j;
		}

		if (tabela[j].stare == LIBER) {
			if (primaStearsa != -1) {
				j = primaStearsa;
			}
			tabela[j].elem = elem;
			tabela[j].frecventa = 1;
			tabela[j].stare = OCUPAT;
			nrElemente++;
			nrDistincte++;
			return;
		}
	}

	if (primaStearsa != -1) {
		tabela[primaStearsa].elem = elem;
		tabela[primaStearsa].frecventa = 1;
		tabela[primaStearsa].stare = OCUPAT;
		nrElemente++;
		nrDistincte++;
	}
}


bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < capacitate; i++) {
		int j = pozitie(elem, i);

		if (tabela[j].stare == LIBER) {
			return false;
		}

		if (tabela[j].stare == OCUPAT && tabela[j].elem == elem) {
			if (tabela[j].frecventa > 1) {
				tabela[j].frecventa--;
			}
			else {
				tabela[j].elem = NULL_TELEM;
				tabela[j].frecventa = 0;
				tabela[j].stare = STERS;
				nrDistincte--;
			}
			nrElemente--;
			if (capacitate > CAPACITATE_MINIMA && nrDistincte * 4 <= capacitate) {
				redimensionareSterge();
			}
			return true;
		}
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	for (int i = 0; i < capacitate; i++) {
		int j = pozitie(elem, i);

		if (tabela[j].stare == LIBER) {
			return false;
		}

		if (tabela[j].stare == OCUPAT && tabela[j].elem == elem) {
			return true;
		}
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	for (int i = 0; i < capacitate; i++) {
		int j = pozitie(elem, i);

		if (tabela[j].stare == LIBER) {
			return 0;
		}

		if (tabela[j].stare == OCUPAT && tabela[j].elem == elem) {
			return tabela[j].frecventa;
		}
	}
	return 0;
}


int Colectie::dim() const {
	return nrElemente;
}


bool Colectie::vida() const {
	return nrElemente == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] tabela;
}
