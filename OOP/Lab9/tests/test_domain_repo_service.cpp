#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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

static void verificaRepo(Repo& repo) {
    assert(repo.repoDim() == 0);
    assert(repo.repoGetAll().empty());
    assert(!repo.repoExista("Lipsa"));

    repo.repoAdd(Film("B", "Drama", 2002, "Actor B"));
    repo.repoAdd(Film("A", "Actiune", 2001, "Actor C"));
    repo.repoAdd(Film("C", "Comedie", 2001, "Actor A"));

    assert(repo.repoDim() == 3);
    assert(repo.repoExista("B"));
    assert(repo.repoExista("A"));
    assert(repo.repoExista("C"));
    assert(repo.repoFind("B").getActor() == "Actor B");

    repo.repoModify("A", Film("A2", "Thriller", 2010, "Actor Z"));
    assert(repo.repoFind("A2").getTitlu() == "A2");
    assert(repo.repoFind("A2").getGen() == "Thriller");
    assert(repo.repoFind("A2").getAn() == 2010);
    assert(repo.repoFind("A2").getActor() == "Actor Z");
    assert(!repo.repoExista("A"));
    assert(repo.repoExista("A2"));

    repo.repoDel("B");
    assert(repo.repoDim() == 2);
    assert(!repo.repoExista("B"));
    assert(repo.repoExista("A2"));
    assert(repo.repoExista("C"));

    bool repoDeleteException = false;
    try {
        repo.repoDel("Lipsa");
    } catch (const RepoError&) {
        repoDeleteException = true;
    }
    assert(repoDeleteException);

    bool repoModifyException = false;
    try {
        repo.repoModify("Lipsa", Film("X", "Y", 1, "Z"));
    } catch (const RepoError&) {
        repoModifyException = true;
    }
    assert(repoModifyException);

    bool repoFindException = false;
    try {
        (void)repo.repoFind("Lipsa");
    } catch (const RepoError&) {
        repoFindException = true;
    }
    assert(repoFindException);
}

static void testRepo() {
    RepoVector repoVector;
    verificaRepo(repoVector);

    RepoMap repoMap;
    verificaRepo(repoMap);
    assert(!repoMap.repoGetAll().empty());
}

static void testService() {
    RepoVector repo;
    Service service(repo);

    const std::map<string, int> raportGol = service.raportGenuri();
    assert(raportGol.empty());

    service.serviceAdd("Dune", "SF", 2021, "Timothee Chalamet");
    service.serviceAdd("Avatar", "Fantasy", 2009, "Sam Worthington");
    service.serviceAdd("Matrix", "SF", 1999, "Keanu Reeves");
    service.serviceAdd("Arrival", "Drama", 2016, "Amy Adams");
    service.serviceAdd("Alien", "Horror", 1979, "Sigourney Weaver");

    assert(service.serviceGetAll().size() == 5);
    assert(service.serviceExista("Avatar"));
    assert(!service.serviceExista("Inexistent"));

    bool duplicateException = false;
    try {
        service.serviceAdd("Dune", "SF", 2021, "Timothee Chalamet");
    } catch (const ServiceError& ex) {
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
    assert(!service.serviceExista("Avatar"));
    assert(service.serviceExista("Avatar 2"));
    assert(service.serviceFind("Avatar 2").getGen() == "SF");
    assert(service.serviceFind("Avatar 2").getAn() == 2022);

    service.undo();
    assert(!service.serviceExista("Avatar 2"));
    assert(service.serviceExista("Avatar"));

    service.serviceModify("Avatar", "Avatar 2", "SF", 2022, "Sam Worthington");

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
    } catch (const ServiceError& ex) {
        modifyMissingException = string(ex.what()) == Service::notFoundErrorMessage;
    }
    assert(modifyMissingException);

    service.serviceDel("Matrix");
    assert(!service.serviceExista("Matrix"));
    assert(service.serviceGetAll().size() == 4);

    service.undo();
    assert(service.serviceExista("Matrix"));
    assert(service.serviceGetAll().size() == 5);

    service.serviceDel("Matrix");

    bool deleteMissingException = false;
    try {
        service.serviceDel("NuExista");
    } catch (const ServiceError& ex) {
        deleteMissingException = string(ex.what()) == Service::notFoundErrorMessage;
    }
    assert(deleteMissingException);

    service.serviceAdd("Blade Runner", "SF", 1982, "Harrison Ford");
    assert(service.serviceExista("Blade Runner"));
    service.undo();
    assert(!service.serviceExista("Blade Runner"));

    RepoVector repoUndoGol;
    Service serviceUndoGol(repoUndoGol);
    bool undoEmptyException = false;
    try {
        serviceUndoGol.undo();
    } catch (const ServiceError&) {
        undoEmptyException = true;
    }
    assert(undoEmptyException);

    bool probabilitateInvalidaException = false;
    try {
        Service serviceProbabilitateInvalida(repoUndoGol, -0.1);
    } catch (const ServiceError&) {
        probabilitateInvalidaException = true;
    }
    assert(probabilitateInvalidaException);

    Service serviceEsuat(repoUndoGol, 1.0);
    bool operatieEsuataException = false;
    try {
        (void)serviceEsuat.serviceExista("Orice");
    } catch (const ServiceError&) {
        operatieEsuataException = true;
    }
    assert(operatieEsuataException);

    string patternTitlu = "Dune";
    const std::vector<const Film*> filtrateTitlu = service.serviceFilter(1, patternTitlu);
    assert(filtrateTitlu.size() == 1);
    assert(filtrateTitlu.at(0)->getTitlu() == "Dune");

    string patternAn = "2022";
    const std::vector<const Film*> filtrateAn = service.serviceFilter(2, patternAn);
    assert(filtrateAn.size() == 1);
    assert(filtrateAn.at(0)->getTitlu() == "Avatar 2");

    string patternInexistent = "1900";
    const std::vector<const Film*> filtrateGoale = service.serviceFilter(2, patternInexistent);
    assert(filtrateGoale.empty());

    bool exceptieAruncata = false;
    string patternInvalid = "abc";
    try {
        (void)service.serviceFilter(2, patternInvalid);
    } catch (const ServiceError&) {
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

    const std::map<string, int> raport = service.raportGenuri();
    assert(raport.at("Drama") == 1);
    assert(raport.at("Horror") == 1);
    assert(raport.at("SF") == 2);

    RepoVector repoAniEgali;
    Service serviceAniEgali(repoAniEgali);
    serviceAniEgali.serviceAdd("Film Z", "Z", 2000, "Actor 1");
    serviceAniEgali.serviceAdd("Film A", "A", 2000, "Actor 2");
    const std::vector<Film> sortateCuAniEgali = serviceAniEgali.serviceSort(3);
    assert(sortateCuAniEgali.size() == 2);
    assert(sortateCuAniEgali.at(0).getGen() == "A");
    assert(sortateCuAniEgali.at(1).getGen() == "Z");

    service.cosAdauga("Dune");
    service.cosAdauga("Alien");
    assert(service.cosGetAll().size() == 2);
    assert(service.cosGetAll().at(0).getTitlu() == "Dune");
    assert(service.cosGetAll().at(1).getTitlu() == "Alien");

    service.cosGoleste();
    assert(service.cosGetAll().empty());

    service.cosAdauga("Dune");
    assert(service.cosGetAll().size() == 1);
    service.cosGenereaza(0);
    assert(service.cosGetAll().empty());

    service.cosAdauga("Dune");
    service.cosAdauga("Alien");
    const string numeFisier = "test_cos.html";
    service.cosSalveazaFisier(numeFisier);

    std::ifstream fin(numeFisier);
    assert(fin.is_open());
    const string continut((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    assert(continut.find("<tr><th>Nr.</th><th>Titlu</th><th>Gen</th><th>An</th><th>Actor</th></tr>") != string::npos);
    assert(continut.find("<td>1</td><td>Dune</td><td>SF</td><td>2021</td><td>Timothee Chalamet</td>") != string::npos);
    assert(continut.find("<td>2</td><td>Alien</td><td>Horror</td><td>1979</td><td>Sigourney Weaver</td>") != string::npos);
    assert(continut.find("<p><b>Nr filme in cos: 2</b></p>") != string::npos);
    fin.close();
    std::remove(numeFisier.c_str());

    service.cosGenereaza(3);
    assert(service.cosGetAll().size() == 3);

    bool cosMissingException = false;
    try {
        service.cosAdauga("NuExista");
    } catch (const ServiceError& ex) {
        cosMissingException = string(ex.what()) == Service::notFoundErrorMessage;
    }
    assert(cosMissingException);

    bool cosInvalidException = false;
    try {
        service.cosGenereaza(-1);
    } catch (const ServiceError&) {
        cosInvalidException = true;
    }
    assert(cosInvalidException);

    RepoVector repoGol;
    Service serviceGol(repoGol);

    bool cosEmptyRepoException = false;
    try {
        serviceGol.cosGenereaza(1);
    } catch (const ServiceError&) {
        cosEmptyRepoException = true;
    }
    assert(cosEmptyRepoException);
}

int main() {
    testDomain();
    testValidator();
    testVector();
    testRepo();
    testService();
    std::cout << "Teste ok.\n";
    return 0;
    
}
