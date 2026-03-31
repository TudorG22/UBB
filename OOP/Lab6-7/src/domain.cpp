#include "domain.h"

Film::Film(const string& titlu, const string& gen, int an, const string& actor)
    : titlu(titlu), gen(gen), an(an), actor(actor) {
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
