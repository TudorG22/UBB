import math

from carte import carte
from client import client

class carte_list:
    """
    Clasa lista pentru obiecte de tip carte.
    """
    def __init__(self) -> None:
        """Initializeaza lista de carti."""
        self.carteList = []

    def get_carteList(self) -> list:
        """Returneaza lista de carti."""
        return self.carteList

    def add_carte(self, book: carte) -> None:
        """Adauga o carte in lista."""
        self.carteList.append(book)

    def remove_carte(self, book: carte) -> None:
        """Sterge o carte din lista dupa id."""
        self.carteList = [b for b in self.carteList if b.get_CarteID() != book.get_CarteID()]

    def replace_carte(self, oldBook: carte, newBook: carte) -> None:
        """Inlocuieste o carte cu alta bazata pe id."""
        for i in range(len(self.carteList)):
            if self.carteList[i].get_CarteID() == oldBook.get_CarteID():
                self.carteList[i] = newBook
                return

    def clear_carti(self) -> None:
        """Goleste lista de carti."""
        self.carteList.clear()

    def __str__(self) -> str:
        """Returneaza lista sub forma text."""
        return "[" + ", ".join(str(book) for book in self.get_carteList()) + "]"


class client_list:
    """
    Clasa lista pentru clienti si cartile imprumutate de acestia.
    """
    def __init__(self) -> None:
        """Initializeaza lista de clienti."""
        self.clientList = []  # [client_object, [book_objects]]

    def get_clientList(self) -> list:
        """Returneaza lista de clienti."""
        return self.clientList

    def add_client(self, cln: client) -> None:
        """Adauga un client nou."""
        self.clientList.append([cln, []])

    def add_carteImprumutata(self, cln: client, book: carte) -> None:
        """Adauga o carte imprumutata unui client."""
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                self.clientList[i][1].append(book)
                return

    def modify_client(self, oldClient: client, newClient: client) -> None:
        """Modifica datele unui client."""
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == oldClient.get_ClientID():
                self.clientList[i][0] = newClient
                return

    def delete_client(self, cln: client) -> None:
        """Sterge un client dupa id."""
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                del self.clientList[i]
                return

    def remove_carteImprumutata(self, cln: client, book: carte) -> None:
        """Sterge o carte imprumutata din lista unui client."""
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                self.clientList[i][1] = [b for b in self.clientList[i][1] if b.get_CarteID() != book.get_CarteID()]
                return

    def clear_clienti(self) -> None:
        """Goleste lista de clienti."""
        self.clientList.clear()

    def carti_inchiriate_statistici(self) -> list:
        """Returneaza (carte, numar_imprumuturi) sortat descrescator dupa numarul de inchirieri."""
        counter = {}
        for _, books in self.clientList:
            for b in books:
                if b.get_CarteID() not in counter:
                    counter[b.get_CarteID()] = [b, 0]
                counter[b.get_CarteID()][1] += 1
        return sorted([(pair[0], pair[1]) for pair in counter.values()], key=lambda t: t[1], reverse=True)

    def clienti_cu_imprumuturi(self) -> list:
        """Returneaza doar clientii care au cel putin o carte imprumutata."""
        return [pair for pair in self.clientList if pair[1]]

    def clienti_cu_imprumuturi_sortati_dupa_nume(self) -> list:
        """Clienti cu imprumuturi ordonati alfabetic dupa nume."""
        return sorted(self.clienti_cu_imprumuturi(), key=lambda pair: pair[0].get_ClientNume())

    def clienti_cu_imprumuturi_sortati_dupa_nr(self) -> list:
        """Clienti cu imprumuturi ordonati descrescator dupa numarul de carti imprumutate, apoi dupa nume."""
        return sorted(self.clienti_cu_imprumuturi(), key=lambda pair: (-len(pair[1]), pair[0].get_ClientNume()))

    def clienti_cei_mai_activi_top20(self) -> list:
        """Returneaza primii 20% dintre clientii cu imprumuturi, ordonati descrescator dupa numarul de carti."""
        clienti_activi = self.clienti_cu_imprumuturi_sortati_dupa_nr()
        if not clienti_activi:
            return []
        limit = max(1, math.ceil(0.2 * len(clienti_activi)))
        return clienti_activi[:limit]

    def autori_inchiriati_statistici(self) -> list:
        """Returneaza (autor, nr imprumuturi) sortat descrescator dupa numarul de imprumuturi, apoi alfabetic."""
        counter = {}
        for _, books in self.clientList:
            for b in books:
                autor = b.get_CarteAutor()
                counter[autor] = counter.get(autor, 0) + 1
        return sorted(counter.items(), key=lambda t: (-t[1], t[0]))
