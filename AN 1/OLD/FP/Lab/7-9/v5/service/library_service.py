import math
from typing import List, Tuple

from domain.carte import Carte
from domain.client import Client
from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository


class LibraryService:
    """Serviciu care orchestreaza operatiile pe carti si clienti."""

    def __init__(self, carte_repo: CarteRepository, client_repo: ClientRepository) -> None:
        self.carte_repo = carte_repo
        self.client_repo = client_repo

    # Carti
    def add_carte(self, carte: Carte) -> None:
        self.carte_repo.add(carte)

    def remove_carte(self, carte_id: int) -> None:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        self.carte_repo.remove(carte_id)

    def replace_carte(self, carte_id: int, carte_noua: Carte) -> None:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        self.carte_repo.replace(carte_id, carte_noua)

    def get_carti(self) -> List[Carte]:
        return self.carte_repo.get_all()

    def clear_carti(self) -> None:
        self.carte_repo.clear()

    def gaseste_carte(self, carte_id: int) -> Carte:
        book = self.carte_repo.find_by_id(carte_id)
        if book is None:
            raise ValueError("Cartea nu exista.")
        return book

    # Clienti
    def add_client(self, client: Client) -> None:
        self.client_repo.add_client(client)

    def delete_client(self, client_id: int) -> None:
        pair = self.client_repo.find_by_id(client_id)
        if pair is None:
            raise ValueError("Clientul nu exista.")
        self.client_repo.delete_client(client_id)

    def modify_client(self, client_id: int, client_nou: Client) -> None:
        pair = self.client_repo.find_by_id(client_id)
        if pair is None:
            raise ValueError("Clientul nu exista.")
        self.client_repo.modify_client(client_id, client_nou)

    def get_clienti(self) -> List[Tuple[Client, List[Carte]]]:
        return self.client_repo.get_all()

    def clear_clienti(self) -> None:
        self.client_repo.clear()

    def gaseste_client(self, client_id: int) -> Tuple[Client, List[Carte]]:
        pair = self.client_repo.find_by_id(client_id)
        if pair is None:
            raise ValueError("Clientul nu exista.")
        return pair

    # Imprumuturi
    def adauga_imprumut(self, client_id: int, carte_id: int) -> None:
        client_pair = self.client_repo.find_by_id(client_id)
        if client_pair is None:
            raise ValueError("Clientul nu exista.")
        carte = self.carte_repo.find_by_id(carte_id)
        if carte is None:
            raise ValueError("Cartea nu exista.")
        self.client_repo.add_imprumut(client_id, carte)

    def sterge_imprumut(self, client_id: int, carte_id: int) -> None:
        client_pair = self.client_repo.find_by_id(client_id)
        if client_pair is None:
            raise ValueError("Clientul nu exista.")
        carte = self.carte_repo.find_by_id(carte_id)
        if carte is None:
            raise ValueError("Cartea nu exista.")
        self.client_repo.remove_imprumut(client_id, carte_id)

    def imprumuturi_client(self, client_id: int) -> List[Carte]:
        client_pair = self.client_repo.find_by_id(client_id)
        if client_pair is None:
            raise ValueError("Clientul nu exista.")
        return client_pair[1]

    # Rapoarte
    def top_carti_inchiriate(self) -> List[Tuple[Carte, int]]:
        counter = {}
        for _, books in self.client_repo.get_all():
            for b in books:
                if b.get_id() not in counter:
                    counter[b.get_id()] = [b, 0]
                counter[b.get_id()][1] += 1
        return sorted(counter.values(), key=lambda t: t[1], reverse=True)

    def clienti_cu_imprumuturi(self) -> List[Tuple[Client, List[Carte]]]:
        return [pair for pair in self.client_repo.get_all() if pair[1]]

    def clienti_cu_imprumuturi_dupa_nume(self) -> List[Tuple[Client, List[Carte]]]:
        return sorted(self.clienti_cu_imprumuturi(), key=lambda pair: pair[0].get_nume())

    def clienti_cu_imprumuturi_dupa_numar(self) -> List[Tuple[Client, List[Carte]]]:
        return sorted(self.clienti_cu_imprumuturi(), key=lambda pair: (-len(pair[1]), pair[0].get_nume()))

    def clienti_top20_activi(self) -> List[Tuple[Client, List[Carte]]]:
        clienti = self.clienti_cu_imprumuturi_dupa_numar()
        if not clienti:
            return []
        limit = max(1, math.ceil(0.2 * len(clienti)))
        return clienti[:limit]

    def autori_inchiriati(self) -> List[Tuple[str, int]]:
        counter = {}
        for _, books in self.client_repo.get_all():
            for b in books:
                counter[b.get_autor()] = counter.get(b.get_autor(), 0) + 1
        return sorted(counter.items(), key=lambda t: (-t[1], t[0]))
