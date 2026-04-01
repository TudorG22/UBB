#include "domain.h"
#include "repo.h"
#include "service.h"

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

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
    assert(repo.repoGetAll()[1].getTitlu() == "A2");
    assert(repo.repoGetAll()[1].getGen() == "Thriller");
    assert(repo.repoGetAll()[1].getAn() == 2010);
    assert(repo.repoGetAll()[1].getActor() == "Actor Z");
    assert(repo.repoCauta("A") == -1);
    assert(repo.repoCauta("A2") == 1);

    repo.repoDel(0);
    assert(repo.repoDim() == 2);
    assert(repo.repoGetAll()[0].getTitlu() == "A2");
    assert(repo.repoGetAll()[1].getTitlu() == "C");
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

    service.serviceModify("Avatar", "Avatar 2", "SF", 2022, "Sam Worthington");
    assert(service.serviceCauta("Avatar") == -1);
    assert(service.serviceCauta("Avatar 2") != -1);
    const auto pozAvatar2 = service.serviceCauta("Avatar 2");
    assert(service.serviceGetAll()[pozAvatar2].getGen() == "SF");
    assert(service.serviceGetAll()[pozAvatar2].getAn() == 2022);

    const auto beforeModify = service.serviceGetAll();
    service.serviceModify("NuExista", "X", "Y", 1, "Z");
    assert(service.serviceGetAll().size() == beforeModify.size());
    for (size_t i = 0; i < beforeModify.size(); ++i) {
        assert(service.serviceGetAll()[i].getTitlu() == beforeModify[i].getTitlu());
    }

    service.serviceDel("Matrix");
    assert(service.serviceCauta("Matrix") == -1);
    assert(service.serviceGetAll().size() == 4);

    const auto beforeDelete = service.serviceGetAll();
    service.serviceDel("NuExista");
    assert(service.serviceGetAll().size() == beforeDelete.size());
    for (size_t i = 0; i < beforeDelete.size(); ++i) {
        assert(service.serviceGetAll()[i].getTitlu() == beforeDelete[i].getTitlu());
    }

    string patternTitlu = "Dune";
    const auto filtrateTitlu = service.serviceFilter(1, patternTitlu);
    assert(filtrateTitlu.size() == 1);
    assert(filtrateTitlu[0]->getTitlu() == "Dune");

    string patternAn = "2022";
    const auto filtrateAn = service.serviceFilter(2, patternAn);
    assert(filtrateAn.size() == 1);
    assert(filtrateAn[0]->getTitlu() == "Avatar 2");

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

    const vector<Film> sortateTitlu = service.serviceSort(1);
    assert(sortateTitlu.size() == 4);
    assert(sortateTitlu[0].getTitlu() == "Alien");
    assert(sortateTitlu[1].getTitlu() == "Arrival");
    assert(sortateTitlu[2].getTitlu() == "Avatar 2");
    assert(sortateTitlu[3].getTitlu() == "Dune");

    const vector<Film> sortateActor = service.serviceSort(2);
    assert(sortateActor[0].getActor() == "Amy Adams");
    assert(sortateActor[1].getActor() == "Sam Worthington");
    assert(sortateActor[2].getActor() == "Sigourney Weaver");
    assert(sortateActor[3].getActor() == "Timothee Chalamet");

    const vector<Film> sortateAnGen = service.serviceSort(3);
    assert(sortateAnGen[0].getTitlu() == "Alien");
    assert(sortateAnGen[1].getTitlu() == "Arrival");
    assert(sortateAnGen[2].getTitlu() == "Dune");
    assert(sortateAnGen[3].getTitlu() == "Avatar 2");

    Repo repoAniEgali;
    Service serviceAniEgali(repoAniEgali);
    serviceAniEgali.serviceAdd("Film Z", "Z", 2000, "Actor 1");
    serviceAniEgali.serviceAdd("Film A", "A", 2000, "Actor 2");
    const vector<Film> sortateCuAniEgali = serviceAniEgali.serviceSort(3);
    assert(sortateCuAniEgali.size() == 2);
    assert(sortateCuAniEgali[0].getGen() == "A");
    assert(sortateCuAniEgali[1].getGen() == "Z");
}

int main() {
    testDomain();
    testRepo();
    testService();
    return 0;
}
