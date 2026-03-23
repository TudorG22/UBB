from Domain.costum import Costum


class CostumRepository:
    def __init__(self) -> None:
        self._storage = []

    def adauga(self, costum: Costum) -> None:
        if self.cauta_dupa_cod(costum.get_cod()) is not None:
            raise ValueError("Exista deja un costum cu acest cod.")
        self._storage.append(costum)

    def cauta_dupa_cod(self, cod: str):
        for item in self._storage:
            if item.get_cod() == cod:
                return item
        return None

    def get_all(self):
        return self._storage[:]
