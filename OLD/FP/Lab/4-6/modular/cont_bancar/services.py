from .entities import (creeaza_tranzactie, get_data, get_suma, get_tip, set_suma, set_tip)
from .date_utils import este_data, este_dupa_data, este_inainte_data


tranzactii = []
istoric = []

def salveaza_stare():
    """
    Salveaza starea curenta a listei de tranzactii in istoric.
    Se face o copie de lista cu dictionare copiate individual (fara deepcopy).
    """
    global istoric
    copie = [dict(tr) for tr in tranzactii]
    istoric.append(copie)

def undo():
    """
    Revine la starea anterioara (daca exista).
    """
    global tranzactii, istoric
    if not istoric:
        print("Nicio operatie de anulat.")
        return
    tranzactii.clear()
    tranzactii.extend(istoric.pop())

def adauga_tranzactie(data: str, suma: int, tip: str) -> None:
    """
    Adauga o tranzactie cu tip in {'intrare','iesire'}.
    Suma se semneaza automat: intrare=pozitiv, iesire=negativ.
    """
    assert(type(data) == str == type(tip) and type(suma) == int)
    assert(este_data(data))
    salveaza_stare()
    tranzactii.append(creeaza_tranzactie(data, suma, tip))

def actualizare_tranzactie(data: str, suma: int, tip: str) -> None:
    """
    Actualizeaza prima tranzactie cu data data.
    """
    assert(type(data) == str == type(tip) and type(suma) == int)
    assert(este_data(data))
    salveaza_stare()
    for element in tranzactii:
        if get_data(element) == data:
            set_suma(element, suma)
            set_tip(element, tip)
            return

def sterge_tranz_data(data: str) -> None:
    """
    Sterge toate tranzactiile care au aceeasi data.
    """
    assert(type(data) == str)
    assert(este_data(data))
    salveaza_stare()
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
    salveaza_stare()
    for element in tranzactii[:]:
        if este_dupa_data(get_data(element), data_inceput) and este_inainte_data(get_data(element), data_final):
            tranzactii.remove(element)

def sterge_tranz_tip(tip: str) -> None:
    """
    Sterge toate tranzactiile de tip 'intrare' sau 'iesire'.
    """
    assert(type(tip) == str)
    assert tip in ("intrare", "iesire")
    salveaza_stare()
    for element in tranzactii[:]:
        if get_tip(element) == tip:
            tranzactii.remove(element)

def tranzactii_peste_suma(suma: int) -> list:
    """
    Returneaza lista tranzactiilor cu suma mai mare decat valoarea data.
    """
    assert type(suma) == int
    return [t for t in tranzactii if get_suma(t) > suma]

def tranzactii_inainte_de_data_si_peste_suma(data: str, suma: int) -> list:
    """
    Returneaza lista tranzactiilor efectuate inainte de o data data
    si cu suma mai mare decat valoarea data.
    """
    assert type(data) == str and este_data(data)
    assert type(suma) == int
    return [t for t in tranzactii if este_inainte_data(get_data(t), data) and get_suma(t) > suma]

def tranzactii_de_tip(tip: str) -> list:
    """
    Returneaza lista tranzactiilor de un anumit tip.
    """
    assert type(tip) == str and tip in ("intrare", "iesire")
    return [t for t in tranzactii if get_tip(t) == tip]

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
        from .entities import get_tip, get_suma, get_data
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
