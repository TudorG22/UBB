from Domain.inchiriere import Inchiriere


class InchiriereRepository:
    def __init__(self) -> None:
        self._storage = []

    def adauga(self, inchiriere: Inchiriere) -> None:
        if self.cauta_dupa_cod(inchiriere.get_cod()) is not None:
            raise ValueError("Exista deja o inchiriere cu acest cod.")
        self._storage.append(inchiriere)

    def cauta_dupa_cod(self, cod: int):
        for item in self._storage:
            if item.get_cod() == cod:
                return item
        return None

    def get_all(self):
        return self._storage[:]

    def __len__(self) -> int:
        return len(self._storage)
