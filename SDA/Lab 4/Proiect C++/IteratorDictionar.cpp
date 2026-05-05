#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	curent = dict.prim;
}


void IteratorDictionar::prim() {
	curent = dict.prim;
}


void IteratorDictionar::urmator() {
	if (!valid()) {
		throw exception();
	}
	curent = dict.urm[curent];
}


TElem IteratorDictionar::element() const{
	if (!valid()) {
		throw exception();
	}
	return dict.elems[curent];
}


bool IteratorDictionar::valid() const {
	return curent != -1;
}

