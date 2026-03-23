# tests.py

from carte import carte
from client import client
from database import carte_list, client_list
from actiuni import gaseste_carte_by_id, gaseste_client_by_id

def assert_equal(a, b, msg=""):
    if a != b:
        raise AssertionError(f"{msg} expected {b}, got {a}")

def test_carte_get_set():
    c = carte(1, "T", "D", "A")
    assert_equal(c.get_CarteID(), 1, "ID initial")
    assert_equal(c.get_CarteTitlu(), "T", "Titlu initial")
    assert_equal(c.get_CarteDescriere(), "D", "Descriere initiala")
    assert_equal(c.get_CarteAutor(), "A", "Autor initial")
    c.set_CarteID(2)
    c.set_CarteTitlu("TT")
    c.set_CarteDescriere("DD")
    c.set_CarteAutor("AA")
    assert_equal(c.get_CarteID(), 2, "ID modificat")
    assert_equal(c.get_CarteTitlu(), "TT", "Titlu modificat")
    assert_equal(c.get_CarteDescriere(), "DD", "Descriere modificata")
    assert_equal(c.get_CarteAutor(), "AA", "Autor modificat")

def test_client_get_set():
    cl = client(10, "N", "C")
    assert_equal(cl.get_ClientID(), 10, "ID initial")
    assert_equal(cl.get_ClientNume(), "N", "Nume initial")
    assert_equal(cl.get_ClientCNP(), "C", "CNP initial")
    cl.set_ClientID(11)
    cl.set_ClientNume("NN")
    cl.set_ClientCNP("CC")
    assert_equal(cl.get_ClientID(), 11, "ID modificat")
    assert_equal(cl.get_ClientNume(), "NN", "Nume modificat")
    assert_equal(cl.get_ClientCNP(), "CC", "CNP modificat")

def test_carte_list_add_and_get():
    l = carte_list()
    b1 = carte(1, "A", "D1", "X")
    b2 = carte(2, "B", "D2", "Y")
    l.add_carte(b1)
    l.add_carte(b2)
    assert_equal(len(l.get_carteList()), 2, "Numar carti")
    assert_equal(l.get_carteList()[0].get_CarteID(), 1, "Prima carte")
    assert_equal(l.get_carteList()[1].get_CarteID(), 2, "A doua carte")

def test_carte_list_remove():
    l = carte_list()
    b1 = carte(1, "A", "D1", "X")
    b2 = carte(2, "B", "D2", "Y")
    l.add_carte(b1)
    l.add_carte(b2)
    l.remove_carte(b1)
    assert_equal([b.get_CarteID() for b in l.get_carteList()], [2], "Dupa stergere b1")

def test_carte_list_replace():
    l = carte_list()
    b1 = carte(1, "A", "D1", "X")
    b2 = carte(2, "B", "D2", "Y")
    b1n = carte(1, "A2", "D1b", "X2")
    l.add_carte(b1)
    l.add_carte(b2)
    l.replace_carte(b1, b1n)
    assert_equal(l.get_carteList()[0].get_CarteTitlu(), "A2", "Titlu inlocuit")
    assert_equal(l.get_carteList()[0].get_CarteAutor(), "X2", "Autor inlocuit")

def test_carte_list_clear_and_str():
    l = carte_list()
    b1 = carte(1, "A", "D1", "X")
    l.add_carte(b1)
    assert_equal(len(l.get_carteList()), 1, "Inainte de clear")
    l.clear_carti()
    assert_equal(len(l.get_carteList()), 0, "Dupa clear")

def test_client_list_add_and_get():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    cl2 = client(20, "N2", "C2")
    cll.add_client(cl1)
    cll.add_client(cl2)
    assert_equal(len(cll.get_clientList()), 2, "Numar clienti")
    assert_equal(cll.get_clientList()[0][0].get_ClientID(), 10, "Primul client")
    assert_equal(cll.get_clientList()[1][0].get_ClientID(), 20, "Al doilea client")

def test_client_list_modify_client():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    cll.add_client(cl1)
    cl_new = client(10, "N1x", "C1x")
    cll.modify_client(cl1, cl_new)
    assert_equal(cll.get_clientList()[0][0].get_ClientNume(), "N1x", "Nume modificat")
    assert_equal(cll.get_clientList()[0][0].get_ClientCNP(), "C1x", "CNP modificat")

def test_client_list_delete_client():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    cl2 = client(20, "N2", "C2")
    cll.add_client(cl1)
    cll.add_client(cl2)
    cll.delete_client(cl1)
    assert_equal([p[0].get_ClientID() for p in cll.get_clientList()], [20], "Stergere client")

def test_client_list_add_and_remove_imprumut():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    b1 = carte(1, "A", "D1", "X")
    b2 = carte(2, "B", "D2", "Y")
    cll.add_client(cl1)
    cll.add_carteImprumutata(cl1, b1)
    cll.add_carteImprumutata(cl1, b2)
    assert_equal([b.get_CarteID() for b in cll.get_clientList()[0][1]], [1, 2], "Imprumuturi adaugate")
    cll.remove_carteImprumutata(cl1, b1)
    assert_equal([b.get_CarteID() for b in cll.get_clientList()[0][1]], [2], "Imprumut eliminat")

def test_client_list_clear_clienti():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    cl2 = client(20, "N2", "C2")
    cll.add_client(cl1)
    cll.add_client(cl2)
    cll.clear_clienti()
    assert_equal(len(cll.get_clientList()), 0, "Clear clienti")




def test_gaseste_carte_by_id():
    l = carte_list()
    b1 = carte(1, "A", "D1", "X")
    b2 = carte(2, "B", "D2", "Y")
    l.add_carte(b1)
    l.add_carte(b2)
    found = gaseste_carte_by_id(l, 2)
    assert_equal(found.get_CarteID(), 2, "Gasire carte existenta")
    not_found = gaseste_carte_by_id(l, 3)
    assert_equal(not_found, None, "Carte inexistenta")

def test_gaseste_client_by_id():
    cll = client_list()
    cl1 = client(10, "N1", "C1")
    cl2 = client(20, "N2", "C2")
    cll.add_client(cl1)
    cll.add_client(cl2)
    pair = gaseste_client_by_id(cll, 20)
    assert_equal(pair[0].get_ClientID(), 20, "Gasire client existent")
    not_pair = gaseste_client_by_id(cll, 30)
    assert_equal(not_pair, None, "Client inexistent")

def all_tests():
    for t in [
        test_carte_get_set,
        test_client_get_set,
        test_carte_list_add_and_get,
        test_carte_list_remove,
        test_carte_list_replace,
        test_carte_list_clear_and_str,
        test_client_list_add_and_get,
        test_client_list_modify_client,
        test_client_list_delete_client,
        test_client_list_add_and_remove_imprumut,
        test_client_list_clear_clienti,
        test_gaseste_carte_by_id,
        test_gaseste_client_by_id,
    ]:
        t()
    print("OK")