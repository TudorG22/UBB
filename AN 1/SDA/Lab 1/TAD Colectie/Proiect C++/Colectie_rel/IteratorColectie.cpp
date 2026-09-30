#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = 0;
	frec_curent = 0;
}

TElem IteratorColectie::element() const{
	if (!valid()) {
		throw std::exception();
	}
	return col.date[curent].first;
}

bool IteratorColectie::valid() const {
	return curent < col.dimensiune;
}

void IteratorColectie::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	frec_curent++;
	if (frec_curent >= col.date[curent].second) {
		curent++;
		frec_curent = 0;
	}
}

void IteratorColectie::prim() {
	curent = 0;
	frec_curent = 0;
}
