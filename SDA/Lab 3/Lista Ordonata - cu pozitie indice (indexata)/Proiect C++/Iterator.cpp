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

bool Iterator::valid() const{
	return curent != nullptr;
}

TElement Iterator::element() const{
	if (!valid()) {
		throw exception();
	}
	return curent->e;
}

