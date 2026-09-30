from typing import List, Optional, Tuple

from domain.carte import Carte
from domain.client import Client


class ClientRepository:
    """
    Repo in memorie pentru clienti si imprumuturile lor.
    """

    def __init__(self) -> None:
        self._clienti: List[Tuple[Client, List[Carte]]] = []

    def get_all(self) -> List[Tuple[Client, List[Carte]]]:
        return self._clienti

    def add_client(self, client: Client) -> None:
        self._clienti.append([client, []])

    def delete_client(self, client_id: int) -> None:
        self._clienti = [pair for pair in self._clienti if pair[0].get_id() != client_id]

    def modify_client(self, client_id: int, client_nou: Client) -> None:
        for i, pair in enumerate(self._clienti):
            if pair[0].get_id() == client_id:
                self._clienti[i][0] = client_nou
                return

    def add_imprumut(self, client_id: int, carte: Carte) -> None:
        for pair in self._clienti:
            if pair[0].get_id() == client_id:
                pair[1].append(carte)
                return

    def remove_imprumut(self, client_id: int, carte_id: int) -> None:
        for pair in self._clienti:
            if pair[0].get_id() == client_id:
                pair[1] = [b for b in pair[1] if b.get_id() != carte_id]
                return

    def clear(self) -> None:
        self._clienti.clear()

    def find_by_id(self, client_id: int) -> Optional[Tuple[Client, List[Carte]]]:
        for pair in self._clienti:
            if pair[0].get_id() == client_id:
                return pair
        return None

    def get_imprumuturi(self, client_id: int) -> List[Carte]:
        pair = self.find_by_id(client_id)
        return [] if pair is None else pair[1]
