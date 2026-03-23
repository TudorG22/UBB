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
