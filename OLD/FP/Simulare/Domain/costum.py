class Costum:
    def __init__(self, cod: str, nume: str, tip: str, pret_pe_zi: float):
        """Initializeaza un costum cu cod, nume, tip si pret pe zi."""
        self._cod = cod
        self._nume = nume
        self._tip = tip
        self._pret_pe_zi = pret_pe_zi

    def get_cod(self) -> str:
        """Returneaza codul costumului"""
        return self._cod

    def get_nume(self) -> str:
        """Returneaza numele costumului."""
        return self._nume

    def get_tip(self) -> str:
        """Returneaza tipul costumului."""
        return self._tip

    def get_pret_pe_zi(self) -> float:
        """Returneaza pretul pe zi al costumului."""
        return self._pret_pe_zi

    def __str__(self) -> str:
        """Intoarce reprezentarea text a costumului."""
        return f"{self._cod}, {self._nume}, {self._tip}, {self._pret_pe_zi}"
