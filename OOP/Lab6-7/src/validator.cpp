#include "validator.h"

ValidationError::ValidationError(const std::string& mesaj)
    : std::runtime_error(mesaj) {
}

void Validator::valideazaFilm(const Film& film) {
    valideazaFilm(film.getTitlu(), film.getGen(), film.getAn(), film.getActor());
}

void Validator::valideazaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor) {
    std::string erori;

    if (titlu.empty()) {
        erori += "Titlu invalid.\n";
    }
    if (gen.empty()) {
        erori += "Gen invalid.\n";
    }
    if (an <= 0) {
        erori += "An invalid.\n";
    }
    if (actor.empty()) {
        erori += "Actor invalid.\n";
    }

    if (!erori.empty()) {
        throw ValidationError(erori);
    }
}
