from Domain.costum import Costum


class Inchiriere:
    def __init__(self, cod: int, costum: Costum, numar_zile: int):
        self._cod = cod
        self._costum = costum
        self._numar_zile = numar_zile

    def get_cod(self) -> int:
        return self._cod

    def get_costum(self) -> Costum:
        return self._costum

    def get_numar_zile(self) -> int:
        return self._numar_zile

    def get_total_price(self, pret_pe_zi: float) -> float:
        return self._numar_zile * pret_pe_zi

    def __str__(self) -> str:
        return f"{self._cod}, {self._costum}, {self._numar_zile}"
