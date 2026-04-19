#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <vector>
#include <stdexcept>
#include <string>

using std::string;

static void testDomain() {
    Film film("Inception", "SF", 2010, "Leonardo DiCaprio");
    assert(film.getTitlu() == "Inception");
    assert(film.getGen() == "SF");
    assert(film.getAn() == 2010);
    assert(film.getActor() == "Leonardo DiCaprio");

    film.setTitlu("Interstellar");
    film.setGen("Drama");
    film.setAn(2014);
    film.setActor("Matthew McConaughey");

    assert(film.getTitlu() == "Interstellar");
    assert(film.getGen() == "Drama");
    assert(film.getAn() == 2014);
    assert(film.getActor() == "Matthew McConaughey");

    Film copie(film);
    assert(copie.getTitlu() == "Interstellar");
    assert(copie.getGen() == "Drama");
    assert(copie.getAn() == 2014);
    assert(copie.getActor() == "Matthew McConaughey");

    Film atribuit("X", "Y", 1, "Z");
    atribuit = film;
    assert(atribuit.getTitlu() == "Interstellar");

    Film mutat(std::move(atribuit));
    assert(mutat.getTitlu() == "Interstellar");

    Film mutareAsignata("A", "B", 2, "C");
    mutareAsignata = std::move(mutat);
    assert(mutareAsignata.getTitlu() == "Interstellar");
}

static void testValidator() {
    Validator::valideazaFilm("Titlu", "Gen", 2000, "Actor");

    bool exceptieAruncata = false;
    try {
        Validator::valideazaFilm("", "", 0, "");
    } catch (const ValidationError&) {
        exceptieAruncata = true;
    }
    assert(exceptieAruncata);
}

static void testVector() {
    std::vector<Film> vector;
    assert(vector.empty());
    assert(vector.size() == 0);

    Film a("A", "Drama", 2001, "Actor A");
    Film b("B", "SF", 2002, "Actor B");
    Film c("C", "Comedie", 2003, "Actor C");

    vector.push_back(a);
    vector.push_back(b);
    vector.push_back(c);
    assert(vector.size() == 3);
    assert(vector.begin()->getTitlu() == "A");
    assert((vector.end() - vector.begin()) == 3);
    assert(vector.at(1).getTitlu() == "B");

    std::vector<Film> copied(vector);
    assert(copied.size() == 3);
    assert(copied.at(2).getTitlu() == "C");

    copied.erase(copied.begin() + 1);
    assert(copied.size() == 2);
    copied.erase(copied.begin());
    assert(copied.size() == 1);
    assert(!copied.empty());

    std::vector<const Film*> filmPointers;
    filmPointers.push_back(&vector.at(0));
    assert(filmPointers.at(0)->getTitlu() == "A");
    filmPointers.push_back(&vector.at(1));
    filmPointers.push_back(&vector.at(2));
    assert(filmPointers.size() == 3);
    assert((filmPointers.end() - filmPointers.begin()) == 3);

    const std::vector<const Film*>& constFilmPointers = filmPointers;
    assert(constFilmPointers.at(0)->getTitlu() == "A");
    assert((constFilmPointers.end() - constFilmPointers.begin()) == 3);

    std::vector<const Film*> filmPointersCopy(filmPointers);
    assert(filmPointersCopy.size() == 3);
    assert(filmPointersCopy.at(1)->getTitlu() == "B");

    filmPointersCopy.erase(filmPointersCopy.begin() + 1);
    assert(filmPointersCopy.size() == 2);
    filmPointersCopy.erase(filmPointersCopy.begin());
    assert(filmPointersCopy.size() == 1);
    assert(!filmPointersCopy.empty());
}

static void testRepo() {
    Repo repo;
    assert(repo.repoDim() == 0);
    assert(repo.repoGetAll().empty());
    assert(repo.repoCauta("Lipsa") == -1);

    repo.repoAdd("B", "Drama", 2002, "Actor B");
    repo.repoAdd("A", "Actiune", 2001, "Actor C");
    repo.repoAdd("C", "Comedie", 2001, "Actor A");

    assert(repo.repoDim() == 3);
    assert(repo.repoCauta("B") == 0);
    assert(repo.repoCauta("A") == 1);
    assert(repo.repoCauta("C") == 2);

    repo.repoModify(1, "A2", "Thriller", 2010, "Actor Z");
    assert(repo.repoGetAll().at(1).getTitlu() == "A2");
    assert(repo.repoGetAll().at(1).getGen() == "Thriller");
    assert(repo.repoGetAll().at(1).getAn() == 2010);
    assert(repo.repoGetAll().at(1).getActor() == "Actor Z");
    assert(repo.repoCauta("A") == -1);
    assert(repo.repoCauta("A2") == 1);

    repo.repoDel(0);
    assert(repo.repoDim() == 2);
    assert(repo.repoGetAll().at(0).getTitlu() == "A2");
    assert(repo.repoGetAll().at(1).getTitlu() == "C");
}

static void testService() {
    Repo repo;
    Service service(repo);

    service.serviceAdd("Dune", "SF", 2021, "Timothee Chalamet");
    service.serviceAdd("Avatar", "Fantasy", 2009, "Sam Worthington");
    service.serviceAdd("Matrix", "SF", 1999, "Keanu Reeves");
    service.serviceAdd("Arrival", "Drama", 2016, "Amy Adams");
    service.serviceAdd("Alien", "Horror", 1979, "Sigourney Weaver");

    assert(service.serviceGetAll().size() == 5);
    assert(service.serviceCauta("Avatar") == 1);
    assert(service.serviceCauta("Inexistent") == -1);

    bool duplicateException = false;
    try {
        service.serviceAdd("Dune", "SF", 2021, "Timothee Chalamet");
    } catch (const std::runtime_error& ex) {
        duplicateException = string(ex.what()) == Service::duplicateErrorMessage;
    }
    assert(duplicateException);

    bool validationException = false;
    try {
        service.serviceAdd("", "SF", -1, "");
    } catch (const ValidationError&) {
        validationException = true;
    }
    assert(validationException);

    service.serviceModify("Avatar", "Avatar 2", "SF", 2022, "Sam Worthington");
    assert(service.serviceCauta("Avatar") == -1);
    assert(service.serviceCauta("Avatar 2") != -1);
    const auto pozAvatar2 = service.serviceCauta("Avatar 2");
    assert(service.serviceGetAll().at(pozAvatar2).getGen() == "SF");
    assert(service.serviceGetAll().at(pozAvatar2).getAn() == 2022);

    bool modifyValidationException = false;
    try {
        service.serviceModify("Avatar 2", "", "Y", 1, "");
    } catch (const ValidationError&) {
        modifyValidationException = true;
    }
    assert(modifyValidationException);

    bool modifyMissingException = false;
    try {
        service.serviceModify("NuExista", "X", "Y", 1, "Z");
    } catch (const std::runtime_error& ex) {
        modifyMissingException = string(ex.what()) == Service::notFoundErrorMessage;
    }
    assert(modifyMissingException);

    service.serviceDel("Matrix");
    assert(service.serviceCauta("Matrix") == -1);
    assert(service.serviceGetAll().size() == 4);

    bool deleteMissingException = false;
    try {
        service.serviceDel("NuExista");
    } catch (const std::runtime_error& ex) {
        deleteMissingException = string(ex.what()) == Service::notFoundErrorMessage;
    }
    assert(deleteMissingException);

    string patternTitlu = "Dune";
    const auto filtrateTitlu = service.serviceFilter(1, patternTitlu);
    assert(filtrateTitlu.size() == 1);
    assert(filtrateTitlu.at(0)->getTitlu() == "Dune");

    string patternAn = "2022";
    const auto filtrateAn = service.serviceFilter(2, patternAn);
    assert(filtrateAn.size() == 1);
    assert(filtrateAn.at(0)->getTitlu() == "Avatar 2");

    string patternInexistent = "1900";
    const auto filtrateGoale = service.serviceFilter(2, patternInexistent);
    assert(filtrateGoale.empty());

    bool exceptieAruncata = false;
    string patternInvalid = "abc";
    try {
        (void)service.serviceFilter(2, patternInvalid);
    } catch (const std::invalid_argument&) {
        exceptieAruncata = true;
    }
    assert(exceptieAruncata);

    const std::vector<Film> sortateTitlu = service.serviceSort(1);
    assert(sortateTitlu.size() == 4);
    assert(sortateTitlu.at(0).getTitlu() == "Alien");
    assert(sortateTitlu.at(1).getTitlu() == "Arrival");
    assert(sortateTitlu.at(2).getTitlu() == "Avatar 2");
    assert(sortateTitlu.at(3).getTitlu() == "Dune");

    const std::vector<Film> sortateActor = service.serviceSort(2);
    assert(sortateActor.at(0).getActor() == "Amy Adams");
    assert(sortateActor.at(1).getActor() == "Sam Worthington");
    assert(sortateActor.at(2).getActor() == "Sigourney Weaver");
    assert(sortateActor.at(3).getActor() == "Timothee Chalamet");

    const std::vector<Film> sortateAnGen = service.serviceSort(3);
    assert(sortateAnGen.at(0).getTitlu() == "Alien");
    assert(sortateAnGen.at(1).getTitlu() == "Arrival");
    assert(sortateAnGen.at(2).getTitlu() == "Dune");
    assert(sortateAnGen.at(3).getTitlu() == "Avatar 2");

    Repo repoAniEgali;
    Service serviceAniEgali(repoAniEgali);
    serviceAniEgali.serviceAdd("Film Z", "Z", 2000, "Actor 1");
    serviceAniEgali.serviceAdd("Film A", "A", 2000, "Actor 2");
    const std::vector<Film> sortateCuAniEgali = serviceAniEgali.serviceSort(3);
    assert(sortateCuAniEgali.size() == 2);
    assert(sortateCuAniEgali.at(0).getGen() == "A");
    assert(sortateCuAniEgali.at(1).getGen() == "Z");
}

int main() {
    testDomain();
    testValidator();
    testVector();
    testRepo();
    testService();
    return 0;
}
