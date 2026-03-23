from Domain.costum import Costum
from Domain.inchiriere import Inchiriere
from Repo.costum_repo import CostumRepository
from Repo.inchiriere_repo import InchiriereRepository
from Validatori.costum_validator import CostumValidator
from Validatori.inchiriere_validator import InchiriereValidator
from Service.service import Service


def ruleaza_teste():
    teste_costum()
    teste_inchiriere()
    teste_service()
    print("Toate testele au trecut.")


def teste_costum():
    c = Costum("c1", "Batman", "supererou", 100.0)
    assert c.get_cod() == "c1"
    assert c.get_nume() == "Batman"
    assert c.get_tip() == "supererou"
    assert c.get_pret_pe_zi() == 100.0
    assert "c1" in str(c)


def teste_inchiriere():
    c = Costum("c1", "Batman", "supererou", 100.0)
    i = Inchiriere(1, c, 3)
    assert i.get_cod() == 1
    assert i.get_costum() is c
    assert i.get_numar_zile() == 3
    assert i.get_total_price(c.get_pret_pe_zi()) == 300.0
    assert "3" in str(i)


def teste_service():
    costum_repo = CostumRepository()
    inchiriere_repo = InchiriereRepository()
    srv = Service(costum_repo, inchiriere_repo, CostumValidator(), InchiriereValidator())

    srv.adauga_costum("c1", "Batman", "supererou", 100.0)
    srv.adauga_costum("c2", "Pirat", "pirat", 50.0)
    costume_sortate = srv.sorteaza_costume("asc")
    assert costume_sortate[0].get_tip() <= costume_sortate[1].get_tip()

    total = srv.adauga_inchiriere(1, "c1", 2)
    assert total == 200.0
    assert len(inchiriere_repo.get_all()) == 1


if __name__ == "__main__":
    ruleaza_teste()
