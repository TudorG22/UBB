from .services import (tranzactii, adauga_tranzactie, actualizare_tranzactie, sterge_tranz_data,
                      sterge_tranz_perioada, sterge_tranz_tip, tranzactii_peste_suma,
                      tranzactii_inainte_de_data_si_peste_suma, tranzactii_de_tip,
                      suma_totala_tip, sold_la_data, tranzactii_tip_ordonate_dupa_suma, undo)
from .entities import get_data, get_suma, get_tip

"""
meniul:

    print(" 1) Adauga tranzactie")

    print(" 3) Filtreaza: elimina tranzactiile de un tip")

    print(" 5) Sterge tranzactii intr-o perioada [inclusiv]")

    print(" 7) Listeaza tranzactiile")
    print(" 8) Afiseaza soldul curent")

    print("15) Undo ultima operatie")

    print(" 0) Iesire")
"""


def add(data, suma, tip):
    adauga_tranzactie(data, suma, tip)
    print("Tranzactie adaugata.")

def filter(t):
    sterge_tranz_tip(t)
    print("Tranzactii de tipul cerut eliminate.")

def delete(d1, d2):
    sterge_tranz_perioada(d1, d2)
    print("Stergere in interval efectuata.")



def prnt():
    if not tranzactii:
        print("(fara tranzactii)")
    else:
        print("\nTranzactii:")
        for i, tr in enumerate(tranzactii, 1):
            print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")
    sold_curent = 0
    for tr in tranzactii:
        if get_tip(tr) == "intrare":
            sold_curent += get_suma(tr)
        elif get_tip(tr) == "iesire":
            sold_curent -= get_suma(tr)
    print(f"Sold curent: {sold_curent}")


def run():
    print("=== Gestionare cont bancar ===")
    print("Tip: intrare/iesire. Suma se semneaza automat (intrare=+, iesire=-).")
    print("Format data: zz.ll.aaaa")

    final = False

    while not final:

        usrInput = input("Input: ")

        commands = usrInput.split('; ')
        for com in commands:
            elements = com.split(' ')

            if elements[0] == "add":
                if len(elements) == 4:
                        data = elements[1]
                        suma = int(elements[2])
                        tip = elements[3]
                        add(data, suma, tip)

            elif elements[0] == "delete":
                if len(elements) == 3:
                        d1 = elements[1]
                        d2 = elements[2]
                        delete(d1, d2)

            elif elements[0] == "filter":
                if len(elements) == 2:
                    t = elements[1]
                    filter(t)

            elif elements[0] == "undo":
                undo()

            elif elements[0] == "print":
                prnt()

            elif elements[0] == "exit":
                final = True