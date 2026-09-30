#include "Iterator.h"
#include "DO.h"
#include <exception>
#include <stack>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	stack<const DO::Nod*> stiva;
	const DO::Nod* curent = dict.radacina;

	while (curent != nullptr || !stiva.empty()) {
		while (curent != nullptr) {
			stiva.push(curent);
			curent = curent->stanga;
		}

		curent = stiva.top();
		stiva.pop();
		elemente.push_back(curent->elem);
		curent = curent->dreapta;
	}

	pozitie = 0;
}

void Iterator::prim(){
	pozitie = 0;
}

void Iterator::urmator(){
	if (!valid()) {
		throw exception();
	}
	pozitie++;
}

bool Iterator::valid() const{
	return pozitie >= 0 && pozitie < (int)elemente.size();
}

TElem Iterator::element() const{
	if (!valid()) {
		throw exception();
	}
	return elemente[pozitie];
}
