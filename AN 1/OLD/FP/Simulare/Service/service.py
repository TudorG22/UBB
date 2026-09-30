from Domain.costum import Costum
from Domain.inchiriere import Inchiriere
from Repo.costum_repo import CostumRepository
from Repo.inchiriere_repo import InchiriereRepository
from Validatori.costum_validator import CostumValidator
from Validatori.inchiriere_validator import InchiriereValidator


class Service:
    def __init__(
        self,
        costum_repo: CostumRepository,
        inchiriere_repo: InchiriereRepository,
        costum_validator: CostumValidator,
        inchiriere_validator: InchiriereValidator,
    ):
        """Initializeaza service-ul cu repo-uri si validatori."""
        self._costum_repo = costum_repo
        self._inchiriere_repo = inchiriere_repo
        self._costum_validator = costum_validator
        self._inchiriere_validator = inchiriere_validator

    def adauga_costum(self, cod: str, nume: str, tip: str, pret_pe_zi: float):
        """Creeaza, valideaza si salveaza un costum."""
        costum = Costum(cod, nume, tip, pret_pe_zi)
        self._costum_validator.valideaza(costum)
        self._costum_repo.adauga(costum)

    def sorteaza_costume(self, ordine: str):
        """Returneaza costumele sortate dupa tip in ordine asc/desc."""
        invers = False
        if ordine == "desc":
            invers = True
        elif ordine != "asc":
            raise ValueError("Ordinea trebuie sa fie 'asc' sau 'desc'.")
        return sorted(self._costum_repo.get_all(), key=lambda c: c.get_tip(), reverse=invers)

    def cauta_costum(self, cod_costum: str):
        """Returneaza costumul dupa cod sau None."""
        return self._costum_repo.cauta_dupa_cod(cod_costum)

    def genereaza_cod_inchiriere(self) -> int:
        """Genereaza un cod nou pentru inchiriere."""
        return len(self._inchiriere_repo.get_all()) + 1

    def adauga_inchiriere(self, cod: int, cod_costum: str, numar_zile: int):
        """Creeaza, valideaza si salveaza o inchiriere; intoarce totalul."""
        costum = self._costum_repo.cauta_dupa_cod(cod_costum)
        if costum is None:
            raise ValueError("Costumul nu exista.")
        inchiriere = Inchiriere(cod, costum, numar_zile)
        self._inchiriere_validator.valideaza(inchiriere)
        self._inchiriere_repo.adauga(inchiriere)
        return inchiriere.get_total_price(costum.get_pret_pe_zi())
