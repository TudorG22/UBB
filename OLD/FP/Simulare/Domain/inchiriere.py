from Domain.costum import Costum


class Inchiriere:
    def __init__(self, cod: int, costum: Costum, numar_zile: int):
        """Initializeaza o inchiriere cu cod, obiect costum si numar de zile."""
        self._cod = cod
        self._costum = costum
        self._numar_zile = numar_zile

    def get_cod(self) -> int:
        """Returneaza codul inchirierii."""
        return self._cod

    def get_costum(self) -> Costum:
        """Returneaza costumul inchiriat."""
        return self._costum

    def get_numar_zile(self) -> int:
        """Returneaza numarul de zile inchiriate."""
        return self._numar_zile

    def get_total_price(self, pret_pe_zi: float) -> float:
        """Calculeaza pretul total pe baza pretului pe zi primit."""
        return self._numar_zile * pret_pe_zi

    def __str__(self) -> str:
        """Intoarce reprezentarea text a inchirierii."""
        return f"{self._cod}, {self._costum}, {self._numar_zile}"
