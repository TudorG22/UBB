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

bool Colectie::bin_search_bool(TElem e) {
	int start = 0;
	int end = dimensiune-1;

	int middle = (start+end)/2;

	while (start <= end){
		if (date[middle].first == e) {
			return true;
		}

		else if (rel(e, date[middle].first)){
			end = middle-1;
			middle = (start+end)/2;
		}

		else {
			start = middle+1;
			middle = (start+end)/2;
		}
	}

	return false;

}

int Colectie::bin_search(TElem e)  {
	int start = 0;
	int end = dimensiune-1;

	int middle = (start+end)/2;

	while (start <= end){
		if (date[middle].first == e) {
			return middle;
		}

		else if (rel(e, date[middle].first)){
			end = middle-1;
			middle = (start+end)/2;
		}

		else {
			start = middle+1;
			middle = (start+end)/2;
		}
	}

	return start;

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


	int index = Colectie::bin_search(e);


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

	
	if (!bin_search_bool(e)) { // -- nu exista --
		return false;
	}

	int index = Colectie::bin_search(e);

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


bool Colectie::cauta(TElem elem)  {
	return bin_search_bool(elem);
}


int Colectie::nrAparitii(TElem elem)  {
	if (!bin_search_bool(elem)) { // -- nu exista --
		return 0;
	}

	int index = Colectie::bin_search(elem);

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
