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
)

print("=== Gestionare biblioteca ===")

def main():
    carti = carte_list()
    clienti = client_list()

    while True:
        meniul()
        opt = input("Optiune: ").strip()

        if opt == "1":
            b = creeaza_carte_din_input()
            carti.add_carte(b)
            print("Cartea a fost adaugata.")
        elif opt == "2":
            cid = citeste_int("ID carte de sters: ")
            b = gaseste_carte_by_id(carti, cid)
            if b is None:
                print("Cartea nu exista.")
            else:
                carti.remove_carte(b)
                print("Cartea a fost stearsa.")
        elif opt == "3":
            cid = citeste_int("ID carte veche: ")
            veche = gaseste_carte_by_id(carti, cid)
            if veche is None:
                print("Cartea veche nu exista.")
            else:
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
            pair = gaseste_client_by_id(clienti, clid)
            if pair is None:
                print("Clientul nu exista.")
            else:
                clienti.delete_client(pair[0])
                print("Client sters.")
        elif opt == "8":
            clid = citeste_int("ID client de modificat: ")
            pair = gaseste_client_by_id(clienti, clid)
            if pair is None:
                print("Clientul nu exista.")
            else:
                print("Introdu noile date ale clientului:")
                cl_nou = creeaza_client_din_input()
                clienti.modify_client(pair[0], cl_nou)
                print("Client modificat.")
        elif opt == "9":
            afiseaza_clienti(clienti)
        elif opt == "10":
            clid = citeste_int("ID client: ")
            cid = citeste_int("ID carte de imprumutat: ")
            pair = gaseste_client_by_id(clienti, clid)
            if pair is None:
                print("Clientul nu exista.")
            else:
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    print("Cartea nu exista in lista de carti.")
                else:
                    clienti.add_carteImprumutata(pair[0], b)
                    print("Cartea a fost adaugata la imprumuturi.")
        elif opt == "11":
            clid = citeste_int("ID client: ")
            cid = citeste_int("ID carte de returnat: ")
            pair = gaseste_client_by_id(clienti, clid)
            if pair is None:
                print("Clientul nu exista.")
            else:
                b = gaseste_carte_by_id(carti, cid)
                if b is None:
                    print("Cartea nu exista in lista de carti.")
                else:
                    clienti.remove_carteImprumutata(pair[0], b)
                    print("Cartea a fost stearsa din imprumuturi.")
        elif opt == "12":
            clid = citeste_int("ID client: ")
            pair = gaseste_client_by_id(clienti, clid)
            if pair is None:
                print("Clientul nu exista.")
            else:
                afiseaza_imprumuturi_client(pair)
        elif opt == "13":
            clienti.clear_clienti()
            print("Lista de clienti a fost golita.")
        elif opt == "0":
            print("Iesire.")
            break
        else:
            print("Optiune invalida.")

