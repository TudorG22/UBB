# ------------------- Cerinta 4 - Cont bancar -------------------

# -------- Stocare --------
# fiecare tranzactie: [data:str, suma:int, tip:str] cu tip in {"intrare","iesire"}
tranzactii = []


# ---------------- Functii ----------------

def creeaza_tranzactie(data: str, suma: int, tip: str) -> list:
    return [data, suma, tip]

def get_data(tr: list) -> str:
    return tr[0]

def get_suma(tr: list) -> int:
    return tr[1]

def get_tip(tr: list) -> str:
    return tr[2]

def set_data(tr: list, data: str) -> None:
    tr[0] = data

def set_suma(tr: list, suma: int) -> None:
    tr[1] = suma

def set_tip(tr: list, tip: str) -> None:
    tr[2] = tip

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
    if len(descompunere) != 3:
        return False

    # testam daca sunt numere
    test1 = True
    for elt in descompunere:
        if not elt.isdigit():
            test1 = False

    # testam daca e o data valida si in ordinea specificata zi-luna-an
    # luna
    test2 = len(descompunere[1]) == 2 and int(descompunere[1]) > 0 and int(descompunere[1]) < 13

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
    Adauga o tranzactie cu tip in {'intrare','iesire'}.
    Suma se semneaza automat: intrare=pozitiv, iesire=negativ.
    """
    assert(type(data) == str == type(tip) and type(suma) == int)
    assert(este_data(data))
    tranzactii.append(creeaza_tranzactie(data, suma, tip))

def actualizare_tranzactie(data: str, suma: int, tip: str) -> None:
    """
    Actualizeaza prima tranzactie cu data data.
    """
    assert(type(data) == str == type(tip) and type(suma) == int)
    assert(este_data(data))
    for element in tranzactii:
        if get_data(element) == data:
            set_suma(element, suma)
            set_tip(element, tip)
            return
    # daca nu exista, nu face nimic (structura ramane neschimbata)

def sterge_tranz_data(data: str) -> None:
    """
    Sterge toate tranzactiile care au aceeasi data.
    """
    assert(type(data) == str)
    assert(este_data(data))
    for element in tranzactii[:]:
        if get_data(element) == data:
            tranzactii.remove(element)

def sterge_tranz_perioada(data_inceput: str, data_final: str) -> None:
    """
    Sterge toate tranzactiile care au data intre data_inceput si data_final.
    """
    assert(type(data_inceput) == str)
    assert(este_data(data_inceput))
    assert(type(data_final) == str)
    assert(este_data(data_final))

    for element in tranzactii[:]:
        if este_dupa_data(get_data(element), data_inceput) and este_inainte_data(get_data(element), data_final):
            tranzactii.remove(element)

def sterge_tranz_tip(tip: str) -> None:
    """
    Sterge toate tranzactiile de tip 'intrare' sau 'iesire'.
    """
    assert(type(tip) == str)
    assert tip in ("intrare", "iesire")
    for element in tranzactii[:]:
        if get_tip(element) == tip:
            tranzactii.remove(element)


def tranzactii_peste_suma(suma: int) -> list:
    """
    Returneaza lista tranzactiilor cu suma mai mare decat valoarea data.
    Parametru:
        - suma: int, valoarea minima.
    Returneaza:
        - lista de tranzactii [data, suma, tip] care respecta conditia.
    """
    assert type(suma) == int
    return [t for t in tranzactii if get_suma(t) > suma]


def tranzactii_inainte_de_data_si_peste_suma(data: str, suma: int) -> list:
    """
    Returneaza lista tranzactiilor efectuate inainte de o data data
    si cu suma mai mare decat valoarea data.
    Parametri:
        - data: str, format 'zz.ll.aaaa'
        - suma: int, valoarea minima
    Returneaza:
        - lista de tranzactii [data, suma, tip] care respecta ambele conditii.
    """
    assert type(data) == str and este_data(data)
    assert type(suma) == int
    return [t for t in tranzactii if este_inainte_data(get_data(t), data) and get_suma(t) > suma]


def tranzactii_de_tip(tip: str) -> list:
    """
    Returneaza lista tranzactiilor de un anumit tip.
    Parametru:
        - tip: str, 'intrare' sau 'iesire'
    Returneaza:
        - lista de tranzactii [data, suma, tip] de tipul specificat.
    """
    assert type(tip) == str and tip in ("intrare", "iesire")
    return [t for t in tranzactii if get_tip(t) == tip]

# --- rapoarte ---

def suma_totala_tip(tip: str) -> int:
    """
    Suma totala a tranzactiilor de un anumit tip.
    Nu schimba semnul sumei; foloseste s direct.
    """
    assert type(tip) == str and tip in ("intrare", "iesire")
    total = 0
    for tr in tranzactii:
        if get_tip(tr) == tip:
            total += get_suma(tr)
    return total


def sold_la_data(data: str) -> int:
    """
    Soldul contului la o data specificata (inclusiv).
    """
    assert type(data) == str and este_data(data)
    sold = 0
    for tr in tranzactii:
        if este_inainte_data(get_data(tr), data):
            if get_tip(tr) == "intrare":
                sold += get_suma(tr)
            elif get_tip(tr) == "iesire":
                sold -= get_suma(tr)
    return sold


def tranzactii_tip_ordonate_dupa_suma(tip: str, crescator: bool = True) -> list:
    """
    Lista tranzactiilor de un anumit tip ordonate dupa suma.
    """
    assert type(tip) == str and tip in ("intrare", "iesire")
    filtrate = [tr for tr in tranzactii if get_tip(tr) == tip]
    return sorted(filtrate, key=lambda tr: get_suma(tr), reverse=not crescator)


# ---------------- Testare ----------------


# ---------------- Interactiune utilizator ----------------

print("=== Gestionare cont bancar ===")
print("Tip: intrare/iesire. Suma se semneaza automat (intrare=+, iesire=-).")
print("Format data: zz.ll.aaaa")

def meniul():
    print("\nMeniu:")
    print(" 1) Adauga tranzactie")
    print(" 2) Actualizeaza tranzactie (dupa data)")
    print(" 3) Filtreaza: elimina tranzactiile de un tip")
    print(" 4) Sterge tranzactii la o data")
    print(" 5) Sterge tranzactii intr-o perioada [inclusiv]")
    print(" 6) Sterge tranzactii dupa tip (intrare/iesire)")
    print(" 7) Listeaza tranzactiile")
    print(" 8) Afiseaza soldul curent")
    print(" 9) Cauta: tranzactii cu sume > o valoare")
    print("10) Cauta: tranzactii inainte de o zi si cu sume > o valoare")
    print("11) Cauta: tranzactii de un anumit tip")
    print("12) Raport: suma totala a tranzactiilor de un tip")
    print("13) Raport: soldul contului la o data")
    print("14) Raport: tranzactii de un tip ordonate dupa suma")
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
        tip = input("Tip (intrare/iesire): ").strip()
        adauga_tranzactie(data, suma, tip)
        print("Tranzactie adaugata.")

    elif opt == "2":
        data = input("Data tranzactiei de actualizat: ").strip()
        suma = int(input("Suma noua (int): ").strip())
        tip = input("Tip nou (intrare/iesire): ").strip()
        actualizare_tranzactie(data, suma, tip)
        print("Tranzactie actualizata.")

    elif opt == "3":
        t = input("Tip tranzactie de eliminat (intrare/iesire): ").strip()
        if not tranzactii:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii:")
            for i, tr in enumerate(tranzactii, 1):
                if get_tip(tr) == t:
                    print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    elif opt == "4":
        data = input("Data pentru stergere (zz.ll.aaaa): ").strip()
        sterge_tranz_data(data)
        print("Stergere completa pentru data data.")

    elif opt == "5":
        d1 = input("Data inceput (zz.ll.aaaa): ").strip()
        d2 = input("Data final (zz.ll.aaaa): ").strip()
        sterge_tranz_perioada(d1, d2)
        print("Stergere in interval efectuata.")

    elif opt == "6":
        t = input("Tip tranzactie de sters (intrare/iesire): ").strip()
        sterge_tranz_tip(t)
        print("Stergere dupa tip efectuata.")

    elif opt == "7":
        if not tranzactii:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii:")
            for i, tr in enumerate(tranzactii, 1):
                print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    elif opt == "8":
        sold_curent = 0
        for tr in tranzactii:
            if get_tip(tr) == "intrare":
                sold_curent += get_suma(tr)
            elif get_tip(tr) == "iesire":
                sold_curent -= get_suma(tr)
        print(f"Sold curent: {sold_curent}")

    elif opt == "9":
        val = int(input("Suma minima (int): ").strip())
        if not tranzactii:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii cu sume > valoarea data:")
            for i, tr in enumerate(tranzactii, 1):
                if get_suma(tr) > val:
                    print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    elif opt == "10":
        zi = input("Zi limita (zz.ll.aaaa): ").strip()
        val = int(input("Suma minima (int): ").strip())
        if not tranzactii:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii inainte de zi si cu sume > valoarea data:")
            for i, tr in enumerate(tranzactii, 1):
                if este_inainte_data(get_data(tr), zi) and get_suma(tr) > val:
                    print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    elif opt == "11":
        t = input("Tip tranzactie cautat (intrare/iesire): ").strip()
        if not tranzactii:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii de tipul cerut:")
            for i, tr in enumerate(tranzactii, 1):
                if get_tip(tr) == t:
                    print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    elif opt == "12":
        t = input("Tip pentru raport (intrare/iesire): ").strip()
        total = suma_totala_tip(t)
        print(f"Suma totala pentru tipul {t}: {total}")

    elif opt == "13":
        zi = input("Data pentru calcul sold (zz.ll.aaaa): ").strip()
        s = sold_la_data(zi)
        print(f"Sold la data {zi}: {s}")

    elif opt == "14":
        t = input("Tip tranzactie (intrare/iesire): ").strip()
        ordinea = input("Ordine (crescator/descrescator): ").strip().lower()
        cresc = True if ordinea == "crescator" else False
        lst = tranzactii_tip_ordonate_dupa_suma(t, crescator=cresc)
        if not lst:
            print("(fara tranzactii)")
        else:
            print("\nTranzactii ordonate dupa suma:")
            for i, tr in enumerate(lst, 1):
                print(f"{i:3d}. {get_data(tr)} | {get_suma(tr)} | {get_tip(tr)}")

    else:
        print("Optiune invalida.")
