from typing import List, Optional

from domain.client import Client


class ClientRepository:
    """
    Repo in memorie pentru clienti.
    """

    def __init__(self) -> None:
        self._clienti: List[Client] = []

    def get_all(self) -> List[Client]:
        return self._clienti

    def add_client(self, client: Client) -> None:
        self._clienti.append(client)

    def delete_client(self, client_id: int) -> None:
        self._clienti = [cl for cl in self._clienti if cl.get_id() != client_id]

    def modify_client(self, client_id: int, client_nou: Client) -> None:
        for i, cl in enumerate(self._clienti):
            if cl.get_id() == client_id:
                self._clienti[i] = client_nou
                return

    def clear(self) -> None:
        self._clienti.clear()

    def find_by_id(self, client_id: int) -> Optional[Client]:
        for cl in self._clienti:
            if cl.get_id() == client_id:
                return cl
        return None
