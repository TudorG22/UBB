from Domain.costum import Costum


class CostumRepository:
    def __init__(self) -> None:
        """Initializeaza stocarea in memorie pentru costume."""
        self._storage = []

    def adauga(self, costum: Costum) -> None:
        """Adauga un costum daca nu exista deja codul."""
        if self.cauta_dupa_cod(costum.get_cod()) is not None:
            raise ValueError("Exista deja un costum cu acest cod.")
        self._storage.append(costum)

    def cauta_dupa_cod(self, cod: str):
        """Cauta un costum dupa cod si il returneaza sau None."""
        for item in self._storage:
            if item.get_cod() == cod:
                return item
        return None

    def get_all(self):
        """Returneaza o copie a listei de costume."""
        return self._storage[:]
