from domain.carte import Carte
from repo.carte_repo import CarteRepository


class CarteRepositoryFile(CarteRepository):
    """Repo pe fisier pentru carti; mosteneste functionalitatea din memorie."""

    def __init__(self, filename: str) -> None:
        super().__init__()
        self._filename = filename
        self._incarca_din_fisier()

    def _incarca_din_fisier(self) -> None:
        try:
            with open(self._filename, "r") as f:
                for line in f:
                    line = line.strip()
                    if not line:
                        continue
                    parts = [p.strip() for p in line.split(",")]
                    if len(parts) != 4:
                        continue
                    cid, titlu, descriere, autor = parts
                    try:
                        cid_int = int(cid)
                    except ValueError:
                        continue
                    self._carti.append(Carte(cid_int, titlu, descriere, autor))
        except FileNotFoundError:
            with open(self._filename, "w"):
                pass

    def _scrie_in_fisier(self) -> None:
        with open(self._filename, "w") as f:
            for carte in self._carti:
                f.write(
                    f"{carte.get_id()},{carte.get_titlu()},{carte.get_descriere()},{carte.get_autor()}\n"
                )

    def add(self, carte: Carte) -> None:
        super().add(carte)
        self._scrie_in_fisier()

    def remove(self, carte_id: int) -> None:
        super().remove(carte_id)
        self._scrie_in_fisier()

    def replace(self, carte_id: int, carte_noua: Carte) -> None:
        super().replace(carte_id, carte_noua)
        self._scrie_in_fisier()

    def clear(self) -> None:
        super().clear()
        self._scrie_in_fisier()
