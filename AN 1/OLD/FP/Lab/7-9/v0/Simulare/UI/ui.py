class Console:
    def __init__(self, service):
        self._srv = service

    def _tipareste_costume_sortate(self):
        ordine = input("Ordine (asc/desc): ").strip()
        costume = self._srv.sorteaza_costume(ordine)
        for costum in costume:
            print(costum)

    def _adauga_inchiriere(self):
        cod_costum = input("Cod costum: ").strip()
        numar_zile = int(input("Numar zile: ").strip())
        cod_inchiriere = self._srv.genereaza_cod_inchiriere()
        costum = self._srv.cauta_costum(cod_costum)
        if costum is None:
            raise ValueError("Costumul nu exista.")
        total = self._srv.adauga_inchiriere(cod_inchiriere, cod_costum, numar_zile)
        print(f"{costum.get_nume()}, {costum.get_tip()}, {total}")

    def run(self):
        comenzi = {
            "1": self._tipareste_costume_sortate,
            "2": self._adauga_inchiriere,
        }
        while True:
            print("1. Sorteaza costume dupa tip")
            print("2. Adauga inchiriere si afiseaza total")
            print("0. Iesire")
            cmd = input("Comanda: ").strip()
            if cmd == "0":
                break
            if cmd in comenzi:
                try:
                    comenzi[cmd]()
                except Exception as ex:
                    print(f"Eroare: {ex}")
            else:
                print("Comanda invalida.")
