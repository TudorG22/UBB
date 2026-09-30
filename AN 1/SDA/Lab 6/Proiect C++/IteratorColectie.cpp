#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = 0;
	aparitieCurenta = 0;
	while (curent < col.capacitate && col.tabela[curent].stare != 1) {
		curent++;
	}
}

void IteratorColectie::prim() {
	curent = 0;
	aparitieCurenta = 0;
	while (curent < col.capacitate && col.tabela[curent].stare != 1) {
		curent++;
	}
}


void IteratorColectie::urmator() {
	if (!valid()) {
		throw std::exception();
	}

	aparitieCurenta++;
	if (aparitieCurenta < col.tabela[curent].frecventa) {
		return;
	}

	curent++;
	aparitieCurenta = 0;
	while (curent < col.capacitate && col.tabela[curent].stare != 1) {
		curent++;
	}
}


bool IteratorColectie::valid() const {
	return curent < col.capacitate;
}



TElem IteratorColectie::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return col.tabela[curent].elem;
}
