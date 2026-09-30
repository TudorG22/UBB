import math
from typing import List, Tuple

from domain.carte import Carte
from domain.client import Client
from domain.imprumut import Imprumut
from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository
from repo.imprumut_repo import ImprumutRepository


class LibraryService:
    """Serviciu care orchestreaza operatiile pe carti, clienti si imprumuturi."""

    def __init__(self, carte_repo: CarteRepository, client_repo: ClientRepository, imprumut_repo: ImprumutRepository) -> None:
        self.carte_repo = carte_repo
        self.client_repo = client_repo
        self.imprumut_repo = imprumut_repo

    # Carti
    def add_carte(self, carte: Carte) -> None:
        self.carte_repo.add(carte)

    def remove_carte(self, carte_id: int) -> None:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        self.carte_repo.remove(carte_id)
        self.imprumut_repo.remove_carte(carte_id)

    def replace_carte(self, carte_id: int, carte_noua: Carte) -> None:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        self.carte_repo.replace(carte_id, carte_noua)
        for imp in self.imprumut_repo.get_all():
            if imp.get_carte().get_id() == carte_id:
                imp.set_carte(carte_noua)
        self.imprumut_repo.save()

    def get_carti(self) -> List[Carte]:
        return self.carte_repo.get_all()

    def clear_carti(self) -> None:
        self.carte_repo.clear()
        self.imprumut_repo.clear()

    def gaseste_carte(self, carte_id: int) -> Carte:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        return book

    # Clienti
    def add_client(self, client: Client) -> None:
        self.client_repo.add_client(client)

    def delete_client(self, client_id: int) -> None:
        cl = self.client_repo.find_by_id(client_id)
        if cl is None:
            raise ValueError("Clientul nu exista.")
        self.client_repo.delete_client(client_id)
        self.imprumut_repo.remove_client(client_id)

    def modify_client(self, client_id: int, client_nou: Client) -> None:
        cl = self.client_repo.find_by_id(client_id)
        if cl is None:
            raise ValueError("Clientul nu exista.")
        self.client_repo.modify_client(client_id, client_nou)
        for imp in self.imprumut_repo.get_all():
            if imp.get_client().get_id() == client_id:
                imp.set_client(client_nou)
        self.imprumut_repo.save()

    def get_clienti(self) -> List[Tuple[Client, List[Carte]]]:
        result = []
        for cl in self.client_repo.get_all():
            carti = [imp.get_carte() for imp in self.imprumut_repo.get_by_client(cl.get_id())]
            result.append((cl, carti))
        return result

    def clear_clienti(self) -> None:
        self.client_repo.clear()
        self.imprumut_repo.clear()

    def gaseste_client(self, client_id: int) -> Tuple[Client, List[Carte]]:
        cl = self.client_repo.find_by_id(client_id)
        if cl is None:
            raise ValueError("Clientul nu exista.")
        carti = [imp.get_carte() for imp in self.imprumut_repo.get_by_client(client_id)]
        return cl, carti

    # Imprumuturi
    def adauga_imprumut(self, client_id: int, carte_id: int) -> None:
        client = self.client_repo.find_by_id(client_id)
        if client is None:
            raise ValueError("Clientul nu exista.")
        carte = self.carte_repo.find_by_id(carte_id)
        if carte is None:
            raise ValueError("Cartea nu exista.")
        self.imprumut_repo.add(Imprumut(client, carte))

    def sterge_imprumut(self, client_id: int, carte_id: int) -> None:
        client = self.client_repo.find_by_id(client_id)
        if client is None:
            raise ValueError("Clientul nu exista.")
        carte = self.carte_repo.find_by_id(carte_id)
        if carte is None:
            raise ValueError("Cartea nu exista.")
        self.imprumut_repo.remove(client_id, carte_id)

    def imprumuturi_client(self, client_id: int) -> List[Carte]:
        cl = self.client_repo.find_by_id(client_id)
        if cl is None:
            raise ValueError("Clientul nu exista.")
        return [imp.get_carte() for imp in self.imprumut_repo.get_by_client(client_id)]

    def imprumuturi_toate(self) -> List[Imprumut]:
        return self.imprumut_repo.get_all()

    # Rapoarte
    def top_carti_inchiriate(self) -> List[Tuple[Carte, int]]:
        counter = {}
        for imp in self.imprumut_repo.get_all():
            book = imp.get_carte()
            if book.get_id() not in counter:
                counter[book.get_id()] = [book, 0]
            counter[book.get_id()][1] += 1
        return self._selection_sort(counter.values(), key=lambda t: t[1], reverse=True)

    def clienti_cu_imprumuturi(self) -> List[Tuple[Client, List[Carte]]]:
        return [(cl, books) for cl, books in self.get_clienti() if books]

    def clienti_cu_imprumuturi_dupa_nume(self) -> List[Tuple[Client, List[Carte]]]:
        return self._selection_sort(self.clienti_cu_imprumuturi(), key=lambda pair: pair[0].get_nume())

    def clienti_cu_imprumuturi_dupa_numar(self) -> List[Tuple[Client, List[Carte]]]:
        return self._shake_sort(self.clienti_cu_imprumuturi(), key=lambda pair: (-len(pair[1]), pair[0].get_nume()))

    def clienti_top20_activi(self) -> List[Tuple[Client, List[Carte]]]:
        clienti = self.clienti_cu_imprumuturi_dupa_numar()
        if not clienti:
            return []
        limit = max(1, math.ceil(0.2 * len(clienti)))
        return clienti[:limit]

    def autori_inchiriati(self) -> List[Tuple[str, int]]:
        counter = self._count_autori_rec(self.imprumut_repo.get_all(), 0, {})
        perechi = list(counter.items())
        return self._selection_sort(perechi, key=lambda t: (-t[1], t[0]))

    def _compara(self, a, b, key, reverse, cmp):
        if cmp is not None:
            res = cmp(a, b)
        else:
            ka, kb = key(a), key(b)
            res = (ka > kb) - (ka < kb)
        return -res if reverse else res

    def _selection_sort(self, items, key=None, reverse=False, cmp=None):
        # Selection sort: parcurgere dubla O(n^2) timp (n pasi, fiecare cauta min pe ~n-i) si O(n) spatiu pentru copia listei
        if key is None:
            key = lambda x: x
        data = list(items)
        n = len(data)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if self._compara(data[min_idx], data[j], key, reverse, cmp) > 0:
                    min_idx = j
            if min_idx != i:
                data[i], data[min_idx] = data[min_idx], data[i]
        return data

    def _shake_sort(self, items, key=None, reverse=False, cmp=None):
        if key is None:
            key = lambda x: x
        data = list(items)
        n = len(data)
        start = 0
        end = n - 1
        while start < end:
            swapped = False
            for i in range(start, end):
                if self._compara(data[i], data[i + 1], key, reverse, cmp) > 0:
                    data[i], data[i + 1] = data[i + 1], data[i]
                    swapped = True
            end -= 1
            for i in range(end, start, -1):
                if self._compara(data[i - 1], data[i], key, reverse, cmp) > 0:
                    data[i], data[i - 1] = data[i - 1], data[i]
                    swapped = True
            start += 1
            if not swapped:
                break
        return data

    def _count_autori_rec(self, imprumuturi, idx, counter):
        if idx == len(imprumuturi):
            return counter
        autor = imprumuturi[idx].get_carte().get_autor()
        counter[autor] = counter.get(autor, 0) + 1
        return self._count_autori_rec(imprumuturi, idx + 1, counter)
