class CostumValidator:
    def valideaza(self, costum):
        erori = []
        if not costum.get_cod():
            erori.append("Codul nu poate fi vid.")
        if not costum.get_nume():
            erori.append("Numele nu poate fi vid.")
        if not costum.get_tip():
            erori.append("Tipul nu poate fi vid.")
        if costum.get_pret_pe_zi() <= 0:
            erori.append("Pretul pe zi trebuie sa fie pozitiv.")
        if erori:
            raise ValueError("\n".join(erori))
