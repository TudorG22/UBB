from Domain.inchiriere import Inchiriere


class InchiriereRepository:
    def __init__(self) -> None:
        """Initializeaza stocarea in memorie pentru inchirieri."""
        self._storage = []

    def adauga(self, inchiriere: Inchiriere) -> None:
        """Adauga o inchiriere daca nu exista deja codul."""
        if self.cauta_dupa_cod(inchiriere.get_cod()) is not None:
            raise ValueError("Exista deja o inchiriere cu acest cod.")
        self._storage.append(inchiriere)

    def cauta_dupa_cod(self, cod: int):
        """Cauta o inchiriere dupa cod si o returneaza sau None."""
        for item in self._storage:
            if item.get_cod() == cod:
                return item
        return None

    def get_all(self):
        """Returneaza o copie a listei de inchirieri."""
        return self._storage[:]

    def __len__(self) -> int:
        """Returneaza numarul de inchirieri din stocare."""
        return len(self._storage)
