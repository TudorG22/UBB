from database import carte_list, client_list
from actiuni import (
    meniul,
    citeste_int,
    creeaza_carte_din_input,
    creeaza_client_din_input,
    gaseste_carte_by_id,
    gaseste_client_by_id,
    afiseaza_clienti,
    afiseaza_imprumuturi_client,
    genereaza_carti,
    genereaza_clienti,
)

def valid_id(x):
    if not isinstance(x, int):
        raise ValueError("ID invalid (trebuie sa fie numar intreg).")

def main():
    print("=== Gestionare biblioteca ===")
    carti = carte_list()
    clienti = client_list()

    while True:
        meniul()
        opt = input("Optiune: ").strip()

        try:
            if opt == "1":
                b = creeaza_carte_din_input()
                carti.add_carte(b)
                print("Cartea a fost adaugata.")

            elif opt == "2":
                cid = citeste_int("ID carte de sters: ")
                valid_id(cid)
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    raise ValueError("Cartea nu exista.")
                carti.remove_carte(b)
                print("Cartea a fost stearsa.")

            elif opt == "3":
                cid = citeste_int("ID carte veche: ")
                valid_id(cid)
                veche = gaseste_carte_by_id(carti, cid)
                if veche is None:
                    raise ValueError("Cartea veche nu exista.")
                print("Introdu date pentru cartea noua:")
                noua = creeaza_carte_din_input()
                carti.replace_carte(veche, noua)
                print("Cartea a fost inlocuita.")

            elif opt == "4":
                if not carti.get_carteList():
                    print("[]")
                else:
                    print(carti)

            elif opt == "5":
                carti.clear_carti()
                print("Lista de carti a fost golita.")

            elif opt == "6":
                cl = creeaza_client_din_input()
                clienti.add_client(cl)
                print("Client adaugat.")

            elif opt == "7":
                clid = citeste_int("ID client de sters: ")
                valid_id(clid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    raise ValueError("Clientul nu exista.")
                clienti.delete_client(pair[0])
                print("Client sters.")

            elif opt == "8":
                clid = citeste_int("ID client de modificat: ")
                valid_id(clid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    raise ValueError("Clientul nu exista.")
                print("Introdu noile date ale clientului:")
                cl_nou = creeaza_client_din_input()
                clienti.modify_client(pair[0], cl_nou)
                print("Client modificat.")

            elif opt == "9":
                afiseaza_clienti(clienti)

            elif opt == "10":
                clid = citeste_int("ID client: ")
                cid = citeste_int("ID carte de imprumutat: ")
                valid_id(clid)
                valid_id(cid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    raise ValueError("Clientul nu exista.")
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    raise ValueError("Cartea nu exista in lista de carti.")
                clienti.add_carteImprumutata(pair[0], b)
                print("Cartea a fost adaugata la imprumuturi.")

            elif opt == "11":
                clid = citeste_int("ID client: ")
                cid = citeste_int("ID carte de returnat: ")
                valid_id(clid)
                valid_id(cid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    raise ValueError("Clientul nu exista.")
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    raise ValueError("Cartea nu exista in lista de carti.")
                clienti.remove_carteImprumutata(pair[0], b)
                print("Cartea a fost stearsa din imprumuturi.")

            elif opt == "12":
                clid = citeste_int("ID client: ")
                valid_id(clid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    raise ValueError("Clientul nu exista.")
                afiseaza_imprumuturi_client(pair)

            elif opt == "13":
                clienti.clear_clienti()
                print("Lista de clienti a fost golita.")

            elif opt == "14":
                cid = citeste_int("ID carte: ")
                valid_id(cid)
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    print("Cartea nu exista.")
                else:
                    print(str(b))

            elif opt == "15":
                clid = citeste_int("ID client: ")
                valid_id(clid)
                pair = gaseste_client_by_id(clienti, clid)
                if pair is None:
                    print("Clientul nu exista.")
                else:
                    cl, books = pair
                    print(f"{cl.get_ClientID()} {cl.get_ClientNume()} {cl.get_ClientCNP()}  |  imprumutate: {len(books)}")

            elif opt == "16":
                nr = citeste_int("Numar carti de generat: ")
                carti_gen = genereaza_carti(nr)
                for elt in carti_gen:
                    carti.add_carte(elt)
                print("Carti generate cu succes.")
                    
            elif opt == "17":
                nr = citeste_int("Numar clienti de generat: ")
                clienti_gen = genereaza_clienti(nr)
                for elt in clienti_gen:
                    clienti.add_client(elt)
                print("Clienti generati cu succes.")

            elif opt == "0":
                print("Iesire.")
                break

            else:
                print("Optiune invalida.")

        except ValueError as e:
            print(f"Eroare: {e}")