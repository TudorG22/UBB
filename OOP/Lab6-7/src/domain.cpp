#include "domain.h"

#include <iostream>

Film::Film(const string& titlu, const string& gen, int an, const string& actor)
    : titlu(titlu), gen(gen), an(an), actor(actor) {
}

Film::Film(const Film& other)
    : titlu(other.titlu), gen(other.gen), an(other.an), actor(other.actor) {
        std::cout << "Copy constructor apelat pentru: " << titlu << '\n';
}

const string& Film::getTitlu() const {
    return titlu;
}

void Film::setTitlu(const string& titluNou) {
    titlu = titluNou;
}

const string& Film::getGen() const {
    return gen;
}

void Film::setGen(const string& genNou) {
    gen = genNou;
}

int Film::getAn() const {
    return an;
}

void Film::setAn(int anNou) {
    an = anNou;
}

const string& Film::getActor() const {
    return actor;
}

void Film::setActor(const string& actorNou) {
    actor = actorNou;
}
