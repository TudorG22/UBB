import random
import string

from domain.carte import Carte
from domain.client import Client
from service.library_service import LibraryService


def meniul() -> None:
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
    print("18) Rapoarte: cele mai inchiriate carti")
    print("19) Rapoarte: clienti cu carti imprumutate ordonati dupa nume")
    print("20) Rapoarte: clienti cu carti imprumutate ordonati dupa numarul de imprumuturi")
    print("21) Rapoarte: primii 20% cei mai activi clienti")
    print("22) Rapoarte: cei mai inchiriati autori")
    print(" 0) Iesire")


def citeste_int(prompt: str):
    val = input(prompt).strip()
    try:
        return int(val)
    except ValueError:
        return val


def creeaza_carte_din_input() -> Carte:
    cid = citeste_int("ID carte: ")
    titlu = input("Titlu: ").strip()
    autor = input("Autor: ").strip()
    descriere = input("Descriere: ").strip()
    return Carte(cid, titlu, descriere, autor)


def creeaza_client_din_input() -> Client:
    clid = citeste_int("ID client: ")
    nume = input("Nume: ").strip()
    cnp = input("CNP: ").strip()
    return Client(clid, nume, cnp)


def valid_id(x):
    if not isinstance(x, int):
        raise ValueError("ID invalid (trebuie sa fie numar intreg).")


def afiseaza_clienti(service: LibraryService) -> None:
    clienti = service.get_clienti()
    if not clienti:
        print("[lista clienti vida]")
        return
    for cl, books in clienti:
        print(f"{cl.get_id()} {cl.get_nume()} {cl.get_cnp()}  |  imprumutate: {len(books)}")


def afiseaza_imprumuturi_client(pair) -> None:
    cl, books = pair
    print(f"Client: {cl.get_id()} {cl.get_nume()} {cl.get_cnp()}")
    if not books:
        print("[fara imprumuturi]")
    else:
        for b in books:
            print(str(b))


def genereaza_carti(nr: int) -> list:
    result = []
    for i in range(1, nr + 1):
        cid = citeste_int(f"ID carte {i}: ")
        titlu = "".join(random.choices(string.ascii_letters + string.digits, k=6))
        autor = "".join(random.choices(string.ascii_letters + string.digits, k=5)) + " " + "".join(random.choices(string.ascii_letters + string.digits, k=5))
        descriere = "".join(random.choices(string.ascii_letters + string.digits, k=15))
        result.append(Carte(cid, titlu, descriere, autor))
    return result


def genereaza_clienti(nr: int) -> list:
    result = []
    for i in range(1, nr + 1):
        clid = citeste_int(f"ID client {i}: ")
        nume = "".join(random.choices(string.ascii_letters + string.digits, k=6)) + " " + "".join(random.choices(string.ascii_letters + string.digits, k=6))
        cnp = random.randint(100, 999)
        result.append(Client(clid, nume, str(cnp)))
    return result


def ruleaza(service: LibraryService) -> None:
    print("=== Gestionare biblioteca (v5) ===")
    while True:
        meniul()
        opt = input("Optiune: ").strip()

        try:
            if opt == "1":
                b = creeaza_carte_din_input()
                valid_id(b.get_id())
                service.add_carte(b)
                print("Cartea a fost adaugata.")

            elif opt == "2":
                cid = citeste_int("ID carte de sters: ")
                valid_id(cid)
                service.remove_carte(cid)
                print("Cartea a fost stearsa.")

            elif opt == "3":
                cid = citeste_int("ID carte veche: ")
                valid_id(cid)
                carte_noua = creeaza_carte_din_input()
                valid_id(carte_noua.get_id())
                service.replace_carte(cid, carte_noua)
                print("Cartea a fost inlocuita.")

            elif opt == "4":
                carti = service.get_carti()
                print("[]" if not carti else "[" + ", ".join(str(b) for b in carti) + "]")

            elif opt == "5":
                service.clear_carti()
                print("Lista de carti a fost golita.")

            elif opt == "6":
                cl = creeaza_client_din_input()
                valid_id(cl.get_id())
                service.add_client(cl)
                print("Client adaugat.")

            elif opt == "7":
                clid = citeste_int("ID client de sters: ")
                valid_id(clid)
                service.delete_client(clid)
                print("Client sters.")

            elif opt == "8":
                clid = citeste_int("ID client de modificat: ")
                valid_id(clid)
                cl_nou = creeaza_client_din_input()
                valid_id(cl_nou.get_id())
                service.modify_client(clid, cl_nou)
                print("Client modificat.")

            elif opt == "9":
                afiseaza_clienti(service)

            elif opt == "10":
                clid = citeste_int("ID client: ")
                cid = citeste_int("ID carte de imprumutat: ")
                valid_id(clid)
                valid_id(cid)
                service.adauga_imprumut(clid, cid)
                print("Cartea a fost adaugata la imprumuturi.")

            elif opt == "11":
                clid = citeste_int("ID client: ")
                cid = citeste_int("ID carte de returnat: ")
                valid_id(clid)
                valid_id(cid)
                service.sterge_imprumut(clid, cid)
                print("Cartea a fost stearsa din imprumuturi.")

            elif opt == "12":
                clid = citeste_int("ID client: ")
                valid_id(clid)
                pair = service.gaseste_client(clid)
                afiseaza_imprumuturi_client(pair)

            elif opt == "13":
                service.clear_clienti()
                print("Lista de clienti a fost golita.")

            elif opt == "14":
                cid = citeste_int("ID carte: ")
                valid_id(cid)
                b = service.gaseste_carte(cid)
                print(str(b))

            elif opt == "15":
                clid = citeste_int("ID client: ")
                valid_id(clid)
                cl, books = service.gaseste_client(clid)
                print(f"{cl.get_id()} {cl.get_nume()} {cl.get_cnp()}  |  imprumutate: {len(books)}")

            elif opt == "16":
                nr = citeste_int("Numar carti de generat: ")
                valid_id(nr)
                for elt in genereaza_carti(nr):
                    valid_id(elt.get_id())
                    service.add_carte(elt)
                print("Carti generate cu succes.")

            elif opt == "17":
                nr = citeste_int("Numar clienti de generat: ")
                valid_id(nr)
                for elt in genereaza_clienti(nr):
                    valid_id(elt.get_id())
                    service.add_client(elt)
                print("Clienti generati cu succes.")

            elif opt == "18":
                stats = service.top_carti_inchiriate()
                if not stats:
                    print("[nicio carte imprumutata]")
                else:
                    for book, cnt in stats:
                        print(f"{book.get_id()} '{book.get_titlu()}' de {book.get_autor()}  |  inchiriata de {cnt} ori")

            elif opt == "19":
                clienti = service.clienti_cu_imprumuturi_dupa_nume()
                if not clienti:
                    print("[niciun client cu imprumuturi]")
                else:
                    for cl, books in clienti:
                        print(f"{cl.get_id()} {cl.get_nume()} {cl.get_cnp()}  |  imprumutate: {len(books)}")

            elif opt == "20":
                clienti = service.clienti_cu_imprumuturi_dupa_numar()
                if not clienti:
                    print("[niciun client cu imprumuturi]")
                else:
                    for cl, books in clienti:
                        print(f"{cl.get_id()} {cl.get_nume()} {cl.get_cnp()}  |  imprumutate: {len(books)}")

            elif opt == "21":
                clienti = service.clienti_top20_activi()
                if not clienti:
                    print("[niciun client cu imprumuturi]")
                else:
                    for cl, books in clienti:
                        print(f"{cl.get_id()} {cl.get_nume()} {cl.get_cnp()}  |  imprumutate: {len(books)}")

            elif opt == "22":
                autori = service.autori_inchiriati()
                if not autori:
                    print("[nicio carte imprumutata]")
                else:
                    for autor, cnt in autori:
                        print(f"{autor}  |  inchiriat in total de {cnt} ori")

            elif opt == "0":
                print("Iesire.")
                break

            else:
                print("Optiune invalida.")

        except ValueError as e:
            print(f"Eroare: {e}")
