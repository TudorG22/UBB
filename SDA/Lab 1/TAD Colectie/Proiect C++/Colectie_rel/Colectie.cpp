#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Colectie::Colectie() {
	capacitate =  10;
	dimensiune = 0;
	dimensiune_real = 0;
	date = new std::pair<TElem,int>[capacitate];
}

void Colectie::adauga(TElem e) {

	// -- dimensiune --
	if (dimensiune == capacitate){
		std::pair<TElem,int>* nou = new std::pair<TElem,int>[capacitate*2];
		for (int j = 0; j < dimensiune; j++) {
			nou[j] = date[j];
		}
		delete[] date;
		date = nou;
		capacitate = capacitate*2;
		
	}


	int index = 0;

	// -- ordine --
	while (index < dimensiune && date[index].first < e) {
		index++;
	}

	if (index < dimensiune && date[index].first != e){	// -- prima instanta --
		for (int j = dimensiune; j > index; j--) {
			date[j] = date[j-1];
		}
		date[index] = std::pair<TElem, int>(e, 1);
		dimensiune++;
	} 	

	else if (index == dimensiune){
		date[index] = std::pair<TElem, int>(e, 1);
		dimensiune++;
	}

	else { // -- instanta suplimentara --
		date[index].second++;
	}

	dimensiune_real++;
}


bool Colectie::sterge(TElem e) {

	int index = 0;

	while (index < dimensiune && date[index].first != e) {
		index++;
	}

	if (index == dimensiune) { // -- nu exista --
		return false;
	}

	if (date[index].second > 1){ // -- exista de mai multe ori --
		date[index].second --;
	}

	else { // -- exista o data --
		for (int j = index; j < dimensiune-1; j++) {
			date[j] = date[j+1];
		}
		dimensiune --;
	}
	
	// -- dimensiune --
	if (dimensiune < capacitate/4 && capacitate/4 >= 10){
		std::pair<TElem,int>* nou = new std::pair<TElem,int>[capacitate/2];
		for (int j = 0; j < dimensiune; j++) {
			nou[j] = date[j];
		}
		delete[] date;
		date = nou;
		capacitate = capacitate/2;
	}

	dimensiune_real --;
	return true;
}


bool Colectie::cauta(TElem elem) const {
	int index = 0;
	while (index < dimensiune && date[index].first != elem) {
		index++;
	}

	if (index == dimensiune) { // -- nu exista --
		return false;
	}

	return true;
}


int Colectie::nrAparitii(TElem elem) const {
	int index = 0;
	while (index < dimensiune && date[index].first != elem) {
		index++;
	}

	if (index == dimensiune) { // -- nu exista --
		return 0;
	}

	return date[index].second;
}


int Colectie::dim() const {
	return dimensiune_real;
}


bool Colectie::vida() const {
	return dimensiune_real == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] date;
}
