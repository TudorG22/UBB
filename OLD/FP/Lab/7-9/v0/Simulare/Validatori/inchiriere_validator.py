class InchiriereValidator:
    def valideaza(self, inchiriere):
        erori = []
        if inchiriere.get_costum() is None:
            erori.append("Costumul trebuie sa existe.")
        if inchiriere.get_numar_zile() <= 0:
            erori.append("Numarul de zile trebuie sa fie pozitiv.")
        if erori:
            raise ValueError("\n".join(erori))
