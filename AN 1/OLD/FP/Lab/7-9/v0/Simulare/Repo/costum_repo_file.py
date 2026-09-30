from pathlib import Path

from Domain.costum import Costum
from Repo.costum_repo import CostumRepository


class CostumRepositoryFile(CostumRepository):
    def __init__(self, filename: str):
        super().__init__()
        path = Path(filename)
        self._filename = path
        self._incarca_din_fisier()

    def _incarca_din_fisier(self):
        with open(self._filename, "r") as f:
            for line in f:
                line = line.strip()
                parts = [p.strip() for p in line.split(",")]
                cod, nume, tip, pret = parts
                self._storage.append(Costum(cod, nume, tip, float(pret)))

    def _salveaza_in_fisier(self):
        with open(self._filename, "w") as f:
            for costum in self._storage:
                f.write(str(costum) + "\n")

    def adauga(self, costum: Costum):
        super().adauga(costum)
        self._salveaza_in_fisier()
