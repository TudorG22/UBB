# ------------------- Cerinta 4 - Cont bancar -------------------

# -------- Stocare --------
# structura de date:
#   - lista de tranzactii, unde o tranzactie e o lista de marime 3 : 
#       [ziua, suma, tip] = [str, int, str] = ["01.12.2000", 0, "mancare"]

tranzactii = []


# -------- Functii --------

# --- testare format data ---

def an_bisect(an: int) -> bool:
    """
    Determina daca un an este bisect.
    Returneaza True daca:
      - an % 400 == 0
      - an % 4 == 0 si an % 100 != 0
    Altfel False.
    """
    if an % 400 == 0:
        return True
    elif an % 100 == 0:
        return False
    elif an % 4 == 0:
        return True
    else:
        return False


def este_data(data: str) -> bool:
    """
    Verifica daca un str reprezinta o data valida in formatul 'zz.ll.aaaa'.
    Returneaza True daca data respecta:
      - toate partile sunt numerice
      - zi, luna, an au dimensiunile si valorile corecte
    """
    descompunere = data.split(".")

    # testam daca sunt numere
    test1 = True
    for elt in descompunere:
        if not elt.isdigit():
            test1 = False

    # testam daca e o data valida si in ordinea specificata zi-luna-an
    # luna
    test2 = len(descompunere[1]) == 2 and int(descompunere[1]) > 0 and int(descompunere[1]) < 12

    # anul
    test4 = len(descompunere[2]) == 4 and int(descompunere[2]) > 0

    # ziua
    test3 = False
    if test2 and test1:
        if int(descompunere[1]) in [1, 3, 5, 7, 8, 10, 12]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 32
        elif int(descompunere[1]) in [4, 6, 7, 9, 11]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 31
        else:
            if test4:
                if an_bisect(int(descompunere[2])):
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 30
                else:
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 29

    return(test1 and test2 and test3 and test4)


# --- comparare date ---  

def este_dupa_data(data_testata: str, data_referinta: str) -> bool:
    """
    Returneaza True daca data_testata >= data_referinta.
    Se verifica in ordinea: an, luna, zi.
    """
    assert(type(data_testata) == type(data_referinta) == str)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int,data_testata.split(".")))
    descompunere_referinta = list(map(int,data_referinta.split(".")))

    if descompunere_test[2] > descompunere_referinta[2]:
        return True
    elif descompunere_test[2] < descompunere_referinta[2]:
        return False

    elif descompunere_test[1] > descompunere_referinta[1]:
        return True
    elif descompunere_test[1] < descompunere_referinta[1]:
        return False 

    else:
        return descompunere_test[0] >= descompunere_referinta[0]


def este_inainte_data(data_testata: str, data_referinta: str) -> bool:
    """
    Returneaza True daca data_testata <= data_referinta.
    Se verifica in ordinea: an, luna, zi.
    """
    assert(type(data_testata) == type(data_referinta) == str)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int,data_testata.split(".")))
    descompunere_referinta = list(map(int,data_referinta.split(".")))

    if descompunere_test[2] < descompunere_referinta[2]:
        return True
    elif descompunere_test[2] > descompunere_referinta[2]:
        return False

    elif descompunere_test[1] < descompunere_referinta[1]:
        return True
    elif descompunere_test[1] > descompunere_referinta[1]:
        return False 

    else:
        return descompunere_test[0] <= descompunere_referinta[0]
    

# --- cerinte ---

def adauga_tranzactie(data: str, suma: int, tip: str) -> None:
    """
    Adauga o tranzactie in lista de tranzactii.
    Fiecare tranzactie are forma [data, suma, tip].
    """
    assert(type(data) == str == type(tip) and type(suma) == int)
    assert(este_data(data))
    tranzactii.append([data, suma, tip])

def actualizare_tranzactie(data: str, suma: int, tip: str) -> None:
    """
    (De implementat) Ar trebui sa actualizeze tranzactia cu data specificata.
    """
    assert(este_data(data))
    assert(type(data) == str == type(tip) and type(suma) == int)

def sterge_tranz_data(data: str) -> None:
    """
    Sterge toate tranzactiile care au aceeasi data.
    """
    assert(type(data) == str)
    assert(este_data(data))
    for element in tranzactii:
        if element[0] == data:
            tranzactii.remove(element)

def sterge_tranz_perioada(data_inceput: str, data_final: str) -> None:
    """
    Sterge toate tranzactiile care au data intre data_inceput si data_final.
    """
    assert(type(data_inceput) == str)
    assert(este_data(data_inceput))
    assert(type(data_final) == str)
    assert(este_data(data_final))

    for element in tranzactii:
        if este_dupa_data(element[0], data_inceput) and este_inainte_data(element[0], data_final):
            tranzactii.remove(element)

def sterge_tranz_tip(tip: str) -> None:
    """
    Sterge toate tranzactiile de un anumit tip (ex: 'mancare', 'transport').
    """
    assert(type(tip) == str)
    for element in tranzactii:
        if element[2] == tip:
            tranzactii.remove(element)


# -------- Testare --------


# -------- Interactiune utilizator --------

if __name__ == "__main__":
    print("=== Gestionare cont bancar ===")
    print("Format data: zz.ll.aaaa | Sume: intregi (pozitiv=incasare, negativ=cheltuiala)")

    def meniul():
        print("\nMeniu:")
        print(" 1) Adauga tranzactie")
        print(" 2) Actualizeaza tranzactie (dupa data)")
        print(" 3) Sterge tranzactii la o data")
        print(" 4) Sterge tranzactii intr-o perioada [inclusiv]")
        print(" 5) Sterge tranzactii dupa tip")
        print(" 6) Listeaza tranzactiile")
        print(" 7) Afiseaza soldul curent")
        print(" 0) Iesire")

    while True:
        meniul()
        opt = input("Alege optiunea: ").strip()

        if opt == "0":
            print("La revedere.")
            break

        elif opt == "1":
            data = input("Data (zz.ll.aaaa): ").strip()
            suma = int(input("Suma (int): ").strip())
            tip = input("Tip (ex: mancare, transport): ").strip()
            adauga_tranzactie(data, suma, tip)
            print("Tranzactie adaugata.")

        elif opt == "2":
            data = input("Data tranzactiei de actualizat: ").strip()
            suma = int(input("Suma noua (int): ").strip())
            tip = input("Tip nou: ").strip()
            actualizare_tranzactie(data, suma, tip)
            print("Tranzactie actualizata.")

        elif opt == "3":
            data = input("Data pentru stergere (zz.ll.aaaa): ").strip()
            sterge_tranz_data(data)
            print("Stergere completa pentru data data.")

        elif opt == "4":
            d1 = input("Data inceput (zz.ll.aaaa): ").strip()
            d2 = input("Data final (zz.ll.aaaa): ").strip()
            sterge_tranz_perioada(d1, d2)
            print("Stergere in interval efectuata.")

        elif opt == "5":
            t = input("Tip tranzactie de sters: ").strip()
            sterge_tranz_tip(t)
            print("Stergere dupa tip efectuata.")

        elif opt == "6":
            if not tranzactii:
                print("(fara tranzactii)")
            else:
                print("\nTranzactii:")
                for i, (d, s, t) in enumerate(tranzactii, 1):
                    print(f"{i:3d}. {d} | {s} | {t}")

        elif opt == "7":
            sold_curent = sum(t[1] for t in tranzactii)
            print(f"Sold curent: {sold_curent}")

        else:
            print("Optiune invalida.")
