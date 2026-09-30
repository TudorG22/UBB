class Costum:
    def __init__(self, cod: str, nume: str, tip: str, pret_pe_zi: float):
        self._cod = cod
        self._nume = nume
        self._tip = tip
        self._pret_pe_zi = pret_pe_zi

    def get_cod(self) -> str:
        return self._cod

    def get_nume(self) -> str:
        return self._nume

    def get_tip(self) -> str:
        return self._tip

    def get_pret_pe_zi(self) -> float:
        return self._pret_pe_zi

    def __str__(self) -> str:
        return f"{self._cod}, {self._nume}, {self._tip}, {self._pret_pe_zi}"
