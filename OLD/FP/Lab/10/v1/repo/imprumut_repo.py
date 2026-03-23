from typing import List

from domain.imprumut import Imprumut


class ImprumutRepository:
    """
    Repo in memorie pentru imprumuturi (obiecte Imprumut).
    """

    def __init__(self) -> None:
        self._imprumuturi: List[Imprumut] = []

    def get_all(self) -> List[Imprumut]:
        return self._imprumuturi

    def add(self, imprumut: Imprumut) -> None:
        self._imprumuturi.append(imprumut)

    def remove(self, client_id: int, carte_id: int) -> None:
        self._imprumuturi = [
            imp for imp in self._imprumuturi
            if not (imp.get_client().get_id() == client_id and imp.get_carte().get_id() == carte_id)
        ]

    def remove_client(self, client_id: int) -> None:
        self._imprumuturi = [imp for imp in self._imprumuturi if imp.get_client().get_id() != client_id]

    def remove_carte(self, carte_id: int) -> None:
        self._imprumuturi = [imp for imp in self._imprumuturi if imp.get_carte().get_id() != carte_id]

    def get_by_client(self, client_id: int) -> List[Imprumut]:
        return [imp for imp in self._imprumuturi if imp.get_client().get_id() == client_id]

    def clear(self) -> None:
        self._imprumuturi.clear()

    def save(self) -> None:
        """Hook pentru repo pe fisier; nu face nimic pentru repo in memorie."""
        return
