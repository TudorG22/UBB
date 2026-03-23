from domain.imprumut import Imprumut
from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository
from repo.imprumut_repo import ImprumutRepository


class ImprumutRepositoryFile(ImprumutRepository):
    """Repo pe fisier pentru imprumuturi, mostenit din cel in memorie."""

    def __init__(self, filename: str, client_repo: ClientRepository, carte_repo: CarteRepository) -> None:
        super().__init__()
        self._filename = filename
        self._client_repo = client_repo
        self._carte_repo = carte_repo
        self._incarca_din_fisier()

    def _incarca_din_fisier(self) -> None:
        try:
            with open(self._filename, "r") as f:
                for line in f:
                    line = line.strip()
                    if not line:
                        continue
                    parts = [p.strip() for p in line.split(",")]
                    if len(parts) != 2:
                        continue
                    client_id_raw, carte_id_raw = parts
                    try:
                        client_id = int(client_id_raw)
                        carte_id = int(carte_id_raw)
                    except ValueError:
                        continue
                    client = self._client_repo.find_by_id(client_id)
                    carte = self._carte_repo.find_by_id(carte_id)
                    if client is None or carte is None:
                        continue
                    self._imprumuturi.append(Imprumut(client, carte))
        except FileNotFoundError:
            with open(self._filename, "w"):
                pass

    def _scrie_in_fisier(self) -> None:
        with open(self._filename, "w") as f:
            for imprumut in self._imprumuturi:
                f.write(f"{imprumut.get_client().get_id()},{imprumut.get_carte().get_id()}\n")

    def add(self, imprumut: Imprumut) -> None:
        super().add(imprumut)
        self._scrie_in_fisier()

    def remove(self, client_id: int, carte_id: int) -> None:
        super().remove(client_id, carte_id)
        self._scrie_in_fisier()

    def remove_client(self, client_id: int) -> None:
        super().remove_client(client_id)
        self._scrie_in_fisier()

    def remove_carte(self, carte_id: int) -> None:
        super().remove_carte(carte_id)
        self._scrie_in_fisier()

    def clear(self) -> None:
        super().clear()
        self._scrie_in_fisier()

    def save(self) -> None:
        """Scrie imprumuturile curente in fisier."""
        self._scrie_in_fisier()
