from carte import carte
from client import client
import random 
import string

def meniul() -> None:
    """Afiseaza meniul principal."""
    print("\nMeniu:")
    print(" 1) Adauga carte")
    print(" 2) Sterge carte")
    print(" 3) Inlocuieste carte")
    print(" 4) Listeaza carti")
    print(" 5) Goleste lista de carti")
    print(" 6) Adauga client")
    print(" 7) Sterge client")
    print(" 8) Modifica client")
    print(" 9) Listeaza clienti")
    print("10) Adauga carte imprumutata unui client")
    print("11) Sterge carte imprumutata de la un client")
    print("12) Afiseaza cartile imprumutate de un client")
    print("13) Goleste lista de clienti")
    print("14) Cauta carte dupa ID")
    print("15) Cauta client dupa ID")
    print("16) Adauga un numar de carti aleatorii")
    print("17) Adauga un numar de clienti aleatorii")
    print(" 0) Iesire")

def citeste_int(prompt: str):
    """Citeste o valoare si incearca sa o converteasca in int."""
    val = input(prompt).strip()
    try:
        return int(val)
    except ValueError:
        return val

def creeaza_carte_din_input() -> carte:
    """Creeaza si returneaza un obiect carte folosind input-ul utilizatorului."""
    cid = citeste_int("ID carte: ")
    titlu = input("Titlu: ").strip()
    autor = input("Autor: ").strip()
    descriere = input("Descriere: ").strip()
    return carte(cid, titlu, descriere, autor)

def creeaza_client_din_input() -> client:
    """Creeaza si returneaza un obiect client folosind input-ul utilizatorului."""
    clid = citeste_int("ID client: ")
    nume = input("Nume: ").strip()
    cnp = input("CNP: ").strip()
    return client(clid, nume, cnp)

def gaseste_carte_by_id(cartl, cid: int) :
    """Cauta si returneaza o carte dupa id. Returneaza None daca nu exista."""
    for b in cartl.get_carteList():
        if b.get_CarteID() == cid:
            return b
    return None

def gaseste_client_by_id(cll, clid: int) :
    """Cauta si returneaza un client dupa id. Returneaza None daca nu exista."""
    for pair in cll.get_clientList():
        if pair[0].get_ClientID() == clid:
            return pair
    return None

def afiseaza_clienti(cll) -> None:
    """Afiseaza toti clientii si numarul de carti imprumutate."""
    if not cll.get_clientList():
        print("[lista clienti vida]")
        return
    for cl, books in cll.get_clientList():
        print(f"{cl.get_ClientID()} {cl.get_ClientNume()} {cl.get_ClientCNP()}  |  imprumutate: {len(books)}")

def afiseaza_imprumuturi_client(pair) -> None:
    """Afiseaza cartile imprumutate de un client."""
    cl, books = pair
    print(f"Client: {cl.get_ClientID()} {cl.get_ClientNume()} {cl.get_ClientCNP()}")
    if not books:
        print("[fara imprumuturi]")
    else:
        for b in books:
            print(str(b))

def genereaza_carti(nr: int) -> list :
    """ Genereaza o lista de carti aleatorii """
    result = []
    for i in range(1, nr+1): 
        cid = citeste_int(f"ID carte {i}: ")
        titlu = ''.join(random.choices(string.ascii_letters + string.digits, k=6))
        autor = ''.join(random.choices(string.ascii_letters + string.digits, k=5)) + ' ' + ''.join(random.choices(string.ascii_letters + string.digits, k=5))
        descriere = ''.join(random.choices(string.ascii_letters + string.digits, k=15))
        result.append(carte(cid, titlu, descriere, autor))
    return(result)

def genereaza_clienti(nr: int) -> list :
    """ Genereaza o lista de clienti aleatorii """
    result = []
    for i in range(1, nr+1): 
        clid = citeste_int(f"ID client {i}: ")
        nume = ''.join(random.choices(string.ascii_letters + string.digits, k=6)) + ' ' + ''.join(random.choices(string.ascii_letters + string.digits, k=6))
        cnp = random.randint(100, 999)
        result.append(client(clid, nume, cnp))
    return(result)