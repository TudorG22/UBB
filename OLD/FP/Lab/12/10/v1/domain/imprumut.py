class Imprumut:
    """
    Imprumut ce leaga un client de o carte.
    """

    def __init__(self, client, carte) -> None:
        self.client = client
        self.carte = carte

    def get_client(self):
        return self.client

    def get_carte(self):
        return self.carte

    def set_client(self, client) -> None:
        self.client = client

    def set_carte(self, carte) -> None:
        self.carte = carte

    def __str__(self) -> str:
        cl = self.get_client()
        book = self.get_carte()
        return f"{cl.get_id()} {cl.get_nume()} -> {book.get_id()}. '{book.get_titlu()}'"
