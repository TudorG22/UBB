from Domain.costum import Costum
from Domain.inchiriere import Inchiriere
from Repo.costum_repo import CostumRepository
from Repo.inchiriere_repo import InchiriereRepository
from Validatori.costum_validator import CostumValidator
from Validatori.inchiriere_validator import InchiriereValidator
from Service.service import Service


def ruleaza_teste():
    """Ruleaza toate testele definite mai jos."""
    teste_costum()
    teste_inchiriere()
    teste_service()
    teste_repo_costum()
    teste_repo_inchiriere()
    print("Toate testele au trecut.")


def teste_costum():
    """Teste pentru entitatea Costum."""
    c = Costum("c1", "Batman", "supererou", 100.0)
    assert c.get_cod() == "c1"
    assert c.get_nume() == "Batman"
    assert c.get_tip() == "supererou"
    assert c.get_pret_pe_zi() == 100.0
    assert "c1" in str(c)


def teste_inchiriere():
    """Teste pentru entitatea Inchiriere."""
    c = Costum("c1", "Batman", "supererou", 100.0)
    i = Inchiriere(1, c, 3)
    assert i.get_cod() == 1
    assert i.get_costum() is c
    assert i.get_numar_zile() == 3
    assert i.get_total_price(c.get_pret_pe_zi()) == 300.0
    assert "3" in str(i)


def teste_service():
    """Teste pentru functionalitatile din service."""
    costum_repo = CostumRepository()
    inchiriere_repo = InchiriereRepository()
    srv = Service(costum_repo, inchiriere_repo, CostumValidator(), InchiriereValidator())

    srv.adauga_costum("c1", "Batman", "supererou", 100.0)
    srv.adauga_costum("c2", "Pirat", "pirat", 50.0)
    costume_sortate = srv.sorteaza_costume("asc")
    assert costume_sortate[0].get_tip() <= costume_sortate[1].get_tip()
    costume_sortate_desc = srv.sorteaza_costume("desc")
    assert costume_sortate_desc[0].get_tip() >= costume_sortate_desc[1].get_tip()
    

    assert srv.cauta_costum("c1").get_nume() == "Batman"
    assert srv.cauta_costum("inexistent") is None
    assert srv.genereaza_cod_inchiriere() == 1

    total = srv.adauga_inchiriere(1, "c1", 2)
    assert total == 200.0
    assert len(inchiriere_repo.get_all()) == 1
    assert srv.genereaza_cod_inchiriere() == 2


def teste_repo_costum():
    """Teste pentru repo-ul de costume."""
    repo = CostumRepository()
    c1 = Costum("c1", "Batman", "supererou", 100.0)
    repo.adauga(c1)
    assert repo.cauta_dupa_cod("c1") is c1
    assert len(repo.get_all()) == 1



def teste_repo_inchiriere():
    """Teste pentru repo-ul de inchirieri."""
    repo = InchiriereRepository()
    c1 = Costum("c1", "Batman", "supererou", 100.0)
    i1 = Inchiriere(1, c1, 2)
    repo.adauga(i1)
    assert repo.cauta_dupa_cod(1) is i1
    assert len(repo.get_all()) == 1


if __name__ == "__main__":
    ruleaza_teste()
