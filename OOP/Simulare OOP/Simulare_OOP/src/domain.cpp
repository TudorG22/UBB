#include "../include/domain.h"

Carte::Carte(int isbn, const string& titlu, const string& autor, const string& gen, int pret, int stoc)
    : isbn{isbn}, titlu{titlu}, autor{autor}, gen{gen}, pret{pret}, stoc{stoc} {
}

int Carte::getIsbn() const {
    return isbn;
}

void Carte::setIsbn(int isbnNou) {
    isbn = isbnNou;
}

const string& Carte::getTitlu() const {
    return titlu;
}

void Carte::setTitlu(const string& titluNou) {
    titlu = titluNou;
}

const string& Carte::getAutor() const {
    return autor;
}

void Carte::setAutor(const string& autorNou) {
    autor = autorNou;
}

const string& Carte::getGen() const {
    return gen;
}

void Carte::setGen(const string& genNou) {
    gen = genNou;
}

int Carte::getPret() const {
    return pret;
}

void Carte::setPret(int pretNou) {
    pret = pretNou;
}

int Carte::getStoc() const {
    return stoc;
}

void Carte::setStoc(int stocNou) {
    stoc = stocNou;
}
