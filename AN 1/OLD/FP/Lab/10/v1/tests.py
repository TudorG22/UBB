import unittest

from domain.carte import Carte
from domain.client import Client
from domain.imprumut import Imprumut
from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository
from repo.imprumut_repo import ImprumutRepository
from service.library_service import LibraryService


class TestEntitatiWhiteBox(unittest.TestCase):
    def test_carte_setters(self):
        carte = Carte(1, "A", "D", "X")
        carte.set_id(2)
        carte.set_titlu("B")
        carte.set_descriere("DD")
        carte.set_autor("Y")
        self.assertEqual((carte.get_id(), carte.get_titlu(), carte.get_descriere(), carte.get_autor()), (2, "B", "DD", "Y"))

    def test_client_setters(self):
        client = Client(1, "Ana", "1")
        client.set_id(2)
        client.set_nume("Bob")
        client.set_cnp("2")
        self.assertEqual((client.get_id(), client.get_nume(), client.get_cnp()), (2, "Bob", "2"))

    def test_imprumut_setters(self):
        cl1 = Client(1, "Ana", "1")
        cl2 = Client(2, "Bob", "2")
        c1 = Carte(1, "T", "D", "A")
        c2 = Carte(2, "T2", "D2", "B")
        imp = Imprumut(cl1, c1)
        imp.set_client(cl2)
        imp.set_carte(c2)
        self.assertEqual((imp.get_client().get_id(), imp.get_carte().get_id()), (2, 2))


class TestRepoWhiteBox(unittest.TestCase):
    def test_carte_repo_add_and_get(self):
        repo = CarteRepository()
        carte = Carte(1, "T", "D", "A")
        repo.add(carte)
        self.assertEqual(repo.get_all(), [carte])

    def test_carte_repo_remove(self):
        repo = CarteRepository()
        repo.add(Carte(1, "T", "D", "A"))
        repo.remove(1)
        self.assertEqual(len(repo.get_all()), 0)

    def test_carte_repo_replace(self):
        repo = CarteRepository()
        repo.add(Carte(1, "T", "D", "A"))
        noua = Carte(1, "TT", "DD", "AA")
        repo.replace(1, noua)
        self.assertIs(repo.find_by_id(1), noua)

    def test_carte_repo_clear(self):
        repo = CarteRepository()
        repo.add(Carte(1, "T", "D", "A"))
        repo.clear()
        self.assertEqual(len(repo.get_all()), 0)

    def test_carte_repo_find_by_id(self):
        repo = CarteRepository()
        repo.add(Carte(1, "T", "D", "A"))
        self.assertIsNotNone(repo.find_by_id(1))
        self.assertIsNone(repo.find_by_id(99))

    def test_client_repo_add_and_get(self):
        repo = ClientRepository()
        client = Client(1, "Ana", "1")
        repo.add_client(client)
        self.assertEqual(repo.get_all(), [client])

    def test_client_repo_delete(self):
        repo = ClientRepository()
        repo.add_client(Client(1, "Ana", "1"))
        repo.delete_client(1)
        self.assertEqual(len(repo.get_all()), 0)

    def test_client_repo_modify(self):
        repo = ClientRepository()
        repo.add_client(Client(1, "Ana", "1"))
        nou = Client(1, "Anca", "2")
        repo.modify_client(1, nou)
        self.assertIs(repo.find_by_id(1), nou)

    def test_client_repo_clear(self):
        repo = ClientRepository()
        repo.add_client(Client(1, "Ana", "1"))
        repo.clear()
        self.assertEqual(len(repo.get_all()), 0)

    def test_client_repo_find_by_id(self):
        repo = ClientRepository()
        repo.add_client(Client(1, "Ana", "1"))
        self.assertIsNotNone(repo.find_by_id(1))
        self.assertIsNone(repo.find_by_id(2))

    def test_imprumut_repo_add_and_get(self):
        repo = ImprumutRepository()
        cl = Client(1, "Ana", "1")
        c = Carte(1, "T", "D", "A")
        imp = Imprumut(cl, c)
        repo.add(imp)
        self.assertEqual(repo.get_all(), [imp])
        self.assertEqual(repo.get_by_client(1), [imp])

    def test_imprumut_repo_remove(self):
        repo = ImprumutRepository()
        cl = Client(1, "Ana", "1")
        c = Carte(1, "T", "D", "A")
        repo.add(Imprumut(cl, c))
        repo.remove(1, 1)
        self.assertEqual(len(repo.get_all()), 0)

    def test_imprumut_repo_remove_client_and_carte(self):
        repo = ImprumutRepository()
        cl = Client(1, "Ana", "1")
        cl2 = Client(2, "Bob", "2")
        c1 = Carte(1, "T", "D", "A")
        c2 = Carte(2, "T2", "D2", "B")
        repo.add(Imprumut(cl, c1))
        repo.add(Imprumut(cl2, c2))
        repo.remove_client(1)
        self.assertEqual([imp.get_client().get_id() for imp in repo.get_all()], [2])
        repo.remove_carte(2)
        self.assertEqual(len(repo.get_all()), 0)

    def test_imprumut_repo_clear(self):
        repo = ImprumutRepository()
        repo.add(Imprumut(Client(1, "A", "1"), Carte(1, "T", "D", "A")))
        repo.clear()
        self.assertEqual(len(repo.get_all()), 0)


class TestServiceWhiteBox(unittest.TestCase):
    def setUp(self):
        self.carti_repo = CarteRepository()
        self.clienti_repo = ClientRepository()
        self.imprumut_repo = ImprumutRepository()
        self.service = LibraryService(self.carti_repo, self.clienti_repo, self.imprumut_repo)

    def _adauga_date(self):
        for c in [Carte(1, "T1", "D1", "A1"), Carte(2, "T2", "D2", "A2"), Carte(3, "T3", "D3", "A1")]:
            self.service.add_carte(c)
        for cl in [Client(1, "Ana", "1"), Client(2, "Bob", "2"), Client(3, "Cristi", "3")]:
            self.service.add_client(cl)

    def test_add_carte(self):
        self.service.add_carte(Carte(1, "T", "D", "A"))
        self.assertEqual(len(self.carti_repo.get_all()), 1)

    def test_remove_carte(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        with self.assertRaises(ValueError):
            self.service.remove_carte(99)
        self.service.remove_carte(1)
        self.assertIsNone(self.carti_repo.find_by_id(1))
        self.assertEqual(len(self.imprumut_repo.get_all()), 0)

    def test_replace_carte(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        with self.assertRaises(ValueError):
            self.service.replace_carte(99, Carte(99, "X", "D", "A"))
        noua = Carte(1, "Nou", "Desc", "Autor")
        self.service.replace_carte(1, noua)
        self.assertIs(self.carti_repo.find_by_id(1), noua)
        self.assertIs(self.imprumut_repo.get_all()[0].get_carte(), noua)

    def test_get_carti(self):
        self._adauga_date()
        self.assertEqual(len(self.service.get_carti()), 3)

    def test_clear_carti(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.clear_carti()
        self.assertEqual(len(self.carti_repo.get_all()), 0)
        self.assertEqual(len(self.imprumut_repo.get_all()), 0)

    def test_gaseste_carte(self):
        self._adauga_date()
        with self.assertRaises(ValueError):
            self.service.gaseste_carte(99)
        self.assertEqual(self.service.gaseste_carte(1).get_titlu(), "T1")

    def test_add_client(self):
        self.service.add_client(Client(1, "Ana", "1"))
        self.assertEqual(len(self.clienti_repo.get_all()), 1)

    def test_delete_client(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        with self.assertRaises(ValueError):
            self.service.delete_client(99)
        self.service.delete_client(1)
        self.assertIsNone(self.clienti_repo.find_by_id(1))
        self.assertEqual(len(self.imprumut_repo.get_all()), 0)

    def test_modify_client(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        with self.assertRaises(ValueError):
            self.service.modify_client(99, Client(99, "X", "X"))
        nou = Client(1, "AnaMaria", "1")
        self.service.modify_client(1, nou)
        self.assertIs(self.clienti_repo.find_by_id(1), nou)
        self.assertIs(self.imprumut_repo.get_all()[0].get_client(), nou)

    def test_get_clienti(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        clienti = self.service.get_clienti()
        self.assertEqual(len(clienti), 3)
        self.assertEqual(len([b for b in clienti if b[0].get_id() == 1][0][1]), 1)

    def test_clear_clienti(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.clear_clienti()
        self.assertEqual(len(self.clienti_repo.get_all()), 0)
        self.assertEqual(len(self.imprumut_repo.get_all()), 0)

    def test_gaseste_client(self):
        self._adauga_date()
        with self.assertRaises(ValueError):
            self.service.gaseste_client(99)
        cl, books = self.service.gaseste_client(1)
        self.assertEqual(cl.get_id(), 1)
        self.assertEqual(len(books), 0)

    def test_adauga_imprumut(self):
        self._adauga_date()
        with self.assertRaises(ValueError):
            self.service.adauga_imprumut(99, 1)
        with self.assertRaises(ValueError):
            self.service.adauga_imprumut(1, 99)
        self.service.adauga_imprumut(1, 1)
        self.assertEqual(len(self.imprumut_repo.get_all()), 1)

    def test_sterge_imprumut(self):
        self._adauga_date()
        with self.assertRaises(ValueError):
            self.service.sterge_imprumut(99, 1)
        with self.assertRaises(ValueError):
            self.service.sterge_imprumut(1, 99)
        self.service.adauga_imprumut(1, 1)
        self.service.sterge_imprumut(1, 1)
        self.assertEqual(len(self.imprumut_repo.get_all()), 0)

    def test_imprumuturi_client(self):
        self._adauga_date()
        with self.assertRaises(ValueError):
            self.service.imprumuturi_client(99)
        self.service.adauga_imprumut(1, 1)
        self.assertEqual([c.get_id() for c in self.service.imprumuturi_client(1)], [1])

    def test_imprumuturi_toate(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.assertEqual(len(self.service.imprumuturi_toate()), 1)

    def test_top_carti_inchiriate(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.adauga_imprumut(2, 1)
        self.service.adauga_imprumut(3, 2)
        top = self.service.top_carti_inchiriate()
        self.assertEqual(top[0][0].get_id(), 1)
        self.assertEqual(top[0][1], 2)

    def test_clienti_cu_imprumuturi(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        clienti = self.service.clienti_cu_imprumuturi()
        self.assertEqual([cl.get_id() for cl, _ in clienti], [1])

    def test_clienti_cu_imprumuturi_dupa_nume(self):
        self._adauga_date()
        self.service.adauga_imprumut(2, 1)
        self.service.adauga_imprumut(1, 2)
        clienti = self.service.clienti_cu_imprumuturi_dupa_nume()
        self.assertEqual([cl.get_nume() for cl, _ in clienti], ["Ana", "Bob"])

    def test_clienti_cu_imprumuturi_dupa_numar(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.adauga_imprumut(1, 2)
        self.service.adauga_imprumut(2, 1)
        clienti = self.service.clienti_cu_imprumuturi_dupa_numar()
        self.assertEqual([cl.get_id() for cl, _ in clienti], [1, 2])

    def test_clienti_top20_activi(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.adauga_imprumut(2, 2)
        self.service.adauga_imprumut(2, 3)
        top = self.service.clienti_top20_activi()
        self.assertEqual([cl.get_id() for cl, _ in top], [2])

    def test_autori_inchiriati(self):
        self._adauga_date()
        self.service.adauga_imprumut(1, 1)
        self.service.adauga_imprumut(2, 3)
        stats = self.service.autori_inchiriati()
        self.assertEqual(stats[0], ("A1", 2))


class TestBlackBox(unittest.TestCase):
    def test_black_box_top_carti(self):
        carti_repo = CarteRepository()
        clienti_repo = ClientRepository()
        imprumut_repo = ImprumutRepository()
        service = LibraryService(carti_repo, clienti_repo, imprumut_repo)
        for c in [Carte(1, "T1", "D1", "A1"), Carte(2, "T2", "D2", "A2")]:
            service.add_carte(c)
        for cl in [Client(1, "Ana", "1"), Client(2, "Bob", "2")]:
            service.add_client(cl)
        service.adauga_imprumut(1, 1)
        service.adauga_imprumut(2, 1)
        service.adauga_imprumut(2, 2)
        rezultat = service.top_carti_inchiriate()
        self.assertEqual([item[0].get_id() for item in rezultat], [1, 2])


if __name__ == "__main__":
    unittest.main()
