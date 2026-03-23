# tests.py pentru v5

from domain.carte import Carte
from domain.client import Client
from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository
from service.library_service import LibraryService


def assert_equal(a, b, msg=""):
    if a != b:
        raise AssertionError(f"{msg} expected {b}, got {a}")


def test_carte_get_set():
    c = Carte(1, "T", "D", "A")
    assert_equal(c.get_id(), 1, "ID initial")
    assert_equal(c.get_titlu(), "T", "Titlu initial")
    assert_equal(c.get_descriere(), "D", "Descriere initiala")
    assert_equal(c.get_autor(), "A", "Autor initial")
    c.set_id(2)
    c.set_titlu("TT")
    c.set_descriere("DD")
    c.set_autor("AA")
    assert_equal(c.get_id(), 2, "ID modificat")
    assert_equal(c.get_titlu(), "TT", "Titlu modificat")
    assert_equal(c.get_descriere(), "DD", "Descriere modificata")
    assert_equal(c.get_autor(), "AA", "Autor modificat")


def test_client_get_set():
    cl = Client(10, "N", "C")
    assert_equal(cl.get_id(), 10, "ID initial")
    assert_equal(cl.get_nume(), "N", "Nume initial")
    assert_equal(cl.get_cnp(), "C", "CNP initial")
    cl.set_id(11)
    cl.set_nume("NN")
    cl.set_cnp("CC")
    assert_equal(cl.get_id(), 11, "ID modificat")
    assert_equal(cl.get_nume(), "NN", "Nume modificat")
    assert_equal(cl.get_cnp(), "CC", "CNP modificat")


def test_carte_repo():
    repo = CarteRepository()
    b1 = Carte(1, "A", "D1", "X")
    b2 = Carte(2, "B", "D2", "Y")
    repo.add(b1)
    repo.add(b2)
    assert_equal(len(repo.get_all()), 2, "Adaugare carti")
    assert_equal(repo.find_by_id(2).get_titlu(), "B", "Gasire carte")
    repo.remove(1)
    assert_equal([c.get_id() for c in repo.get_all()], [2], "Dupa stergere")
    repo.replace(2, Carte(2, "BB", "D2", "Z"))
    assert_equal(repo.find_by_id(2).get_autor(), "Z", "Inlocuire")
    repo.clear()
    assert_equal(len(repo.get_all()), 0, "Clear carti")


def test_client_repo():
    repo = ClientRepository()
    cl1 = Client(1, "Ana", "1")
    cl2 = Client(2, "Bob", "2")
    b1 = Carte(10, "T1", "D1", "A1")
    repo.add_client(cl1)
    repo.add_client(cl2)
    repo.add_imprumut(1, b1)
    assert_equal(len(repo.get_imprumuturi(1)), 1, "Imprumut adaugat")
    repo.remove_imprumut(1, 10)
    assert_equal(len(repo.get_imprumuturi(1)), 0, "Imprumut sters")
    repo.modify_client(2, Client(2, "Bobby", "2"))
    assert_equal(repo.find_by_id(2)[0].get_nume(), "Bobby", "Modificare client")
    repo.delete_client(1)
    assert_equal([p[0].get_id() for p in repo.get_all()], [2], "Stergere client")
    repo.clear()
    assert_equal(len(repo.get_all()), 0, "Clear clienti")


def test_service_rapoarte():
    carti_repo = CarteRepository()
    clienti_repo = ClientRepository()
    srv = LibraryService(carti_repo, clienti_repo)

    b1 = Carte(1, "T1", "D1", "A1")
    b2 = Carte(2, "T2", "D2", "A2")
    b3 = Carte(3, "T3", "D3", "A1")
    for b in [b1, b2, b3]:
        srv.add_carte(b)

    c1 = Client(1, "Ana", "1")
    c2 = Client(2, "Bob", "2")
    c3 = Client(3, "Cristi", "3")
    for c in [c1, c2, c3]:
        srv.add_client(c)

    srv.adauga_imprumut(1, 1)
    srv.adauga_imprumut(1, 2)
    srv.adauga_imprumut(2, 1)
    srv.adauga_imprumut(2, 3)

    top_carti = srv.top_carti_inchiriate()
    assert_equal(top_carti[0][0].get_id(), 1, "Cartea cea mai inchiriata")
    assert_equal(top_carti[0][1], 2, "Numar inchirieri carte 1")

    dupa_nume = srv.clienti_cu_imprumuturi_dupa_nume()
    assert_equal([p[0].get_nume() for p in dupa_nume], ["Ana", "Bob"], "Clienti dupa nume")

    dupa_nr = srv.clienti_cu_imprumuturi_dupa_numar()
    assert_equal([p[0].get_nume() for p in dupa_nr], ["Ana", "Bob"], "Clienti dupa numar")

    top20 = srv.clienti_top20_activi()
    assert_equal(len(top20), 1, "Top 20% minim 1")
    assert_equal(top20[0][0].get_nume(), "Ana", "Cel mai activ")

    autori = srv.autori_inchiriati()
    assert_equal(autori[0][0], "A1", "Autor top")
    assert_equal(autori[0][1], 3, "Numar imprumuturi autor A1")


def all_tests():
    for t in [
        test_carte_get_set,
        test_client_get_set,
        test_carte_repo,
        test_client_repo,
        test_service_rapoarte,
    ]:
        t()
    print("OK")


if __name__ == "__main__":
    all_tests()
