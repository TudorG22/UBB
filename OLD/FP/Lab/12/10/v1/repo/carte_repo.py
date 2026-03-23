from typing import List, Optional

from domain.carte import Carte


class CarteRepository:
    """
    Repo in memorie pentru carti.
    """

    def __init__(self) -> None:
        self._carti: List[Carte] = []

    def get_all(self) -> List[Carte]:
        return self._carti

    def add(self, carte: Carte) -> None:
        self._carti.append(carte)

    def remove(self, carte_id: int) -> None:
        self._carti = [b for b in self._carti if b.get_id() != carte_id]

    def replace(self, carte_id: int, carte_noua: Carte) -> None:
        for i, c in enumerate(self._carti):
            if c.get_id() == carte_id:
                self._carti[i] = carte_noua
                return

    def clear(self) -> None:
        self._carti.clear()

    def find_by_id(self, carte_id: int) -> Optional[Carte]:
        for c in self._carti:
            if c.get_id() == carte_id:
                return c
        return None
