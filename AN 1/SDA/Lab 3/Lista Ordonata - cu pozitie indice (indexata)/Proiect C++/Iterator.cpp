#include "Iterator.h"
#include "LO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const LO& lo) : lista(lo){
	curent = lista.prim;
}

void Iterator::prim() {
	curent = lista.prim;
}

void Iterator::urmator(){
	if (!valid()) {
		throw exception();
	}
	curent = curent->urm;
}

void Iterator::avanseazaKPasi(int k){
	if (!valid() || k <= 0) {
		throw exception();
	}

	for (int i=0; i<k; i++){
		if (curent != nullptr) curent = curent->urm;
	}
}

bool Iterator::valid() const{
	return curent != nullptr;
}

TElement Iterator::element() const{
	if (!valid()) {
		throw exception();
	}
	return curent->e;
}

