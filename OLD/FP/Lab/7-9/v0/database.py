from carte import carte
from client import client

class carte_list:
    def __init__(self):
        self.carteList = []

    def get_carteList(self):
        return self.carteList

    def add_carte(self, book):
        self.carteList.append(book)

    def remove_carte(self, book):
        self.carteList = [b for b in self.carteList if b.get_CarteID() != book.get_CarteID()]

    def replace_carte(self, oldBook, newBook):
        for i in range(len(self.carteList)):
            if self.carteList[i].get_CarteID() == oldBook.get_CarteID():
                self.carteList[i] = newBook
                return

    def clear_carti(self):
        self.carteList.clear()

    def __str__(self):
        return "[" + ", ".join(str(book) for book in self.get_carteList()) + "]"


class client_list:
    def __init__(self):
        self.clientList = []  # [client_object, [book_objects]]

    def get_clientList(self):
        return self.clientList

    def add_client(self, cln):
        self.clientList.append([cln, []])

    def add_carteImprumutata(self, cln, book):
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                self.clientList[i][1].append(book)
                return

    def modify_client(self, oldClient, newClient):
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == oldClient.get_ClientID():
                self.clientList[i][0] = newClient
                return

    def delete_client(self, cln):
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                del self.clientList[i]
                return

    def remove_carteImprumutata(self, cln, book):
        for i in range(len(self.clientList)):
            if self.clientList[i][0].get_ClientID() == cln.get_ClientID():
                self.clientList[i][1] = [b for b in self.clientList[i][1] if b.get_CarteID() != book.get_CarteID()]
                return

    def clear_clienti(self):
        self.clientList.clear()
