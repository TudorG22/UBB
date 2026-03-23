from domain.client import Client
from repo.client_repo import ClientRepository


class ClientRepositoryFile(ClientRepository):
    """Repo pe fisier pentru clienti; mosteneste functionalitatea in memorie."""

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
                    if len(parts) != 3:
                        continue
                    cid, nume, cnp = parts
                    try:
                        cid_int = int(cid)
                    except ValueError:
                        continue
                    self._clienti.append(Client(cid_int, nume, cnp))
        except FileNotFoundError:
            with open(self._filename, "w"):
                pass

    def _scrie_in_fisier(self) -> None:
        with open(self._filename, "w") as f:
            for client in self._clienti:
                f.write(f"{client.get_id()},{client.get_nume()},{client.get_cnp()}\n")

    def add_client(self, client: Client) -> None:
        super().add_client(client)
        self._scrie_in_fisier()

    def delete_client(self, client_id: int) -> None:
        super().delete_client(client_id)
        self._scrie_in_fisier()

    def modify_client(self, client_id: int, client_nou: Client) -> None:
        super().modify_client(client_id, client_nou)
        self._scrie_in_fisier()

    def clear(self) -> None:
        super().clear()
        self._scrie_in_fisier()
