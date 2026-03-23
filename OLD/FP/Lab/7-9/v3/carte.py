class carte:
    """
    Clasa carte. Pastreaza datele intr-o singura lista:
    [id, titlu, descriere, autor]
    """
    def __init__(self, id: int, titlu: str, descriere: str, autor: str) -> None:
        """Initializeaza o carte folosind id, titlu, descriere, autor."""
        self.date = [id, titlu, descriere, autor]

    def get_CarteID(self) -> int:
        """Returneaza id-ul cartii."""
        return self.date[0]

    def get_CarteTitlu(self) -> str:
        """Returneaza titlul cartii."""
        return self.date[1]

    def get_CarteDescriere(self) -> str:
        """Returneaza descrierea cartii."""
        return self.date[2]

    def get_CarteAutor(self) -> str:
        """Returneaza autorul cartii."""
        return self.date[3]

    def set_CarteID(self, id: int) -> None:
        """Seteaza id-ul cartii."""
        self.date[0] = id

    def set_CarteTitlu(self, titlu: str) -> None:
        """Seteaza titlul cartii."""
        self.date[1] = titlu

    def set_CarteDescriere(self, descriere: str) -> None:
        """Seteaza descrierea cartii."""
        self.date[2] = descriere

    def set_CarteAutor(self, autor: str) -> None:
        """Seteaza autorul cartii."""
        self.date[3] = autor

    def __str__(self) -> str:
        """Returneaza o reprezentare text a cartii."""
        return f"{self.get_CarteID()}. '{self.get_CarteTitlu()}' scrisa de {self.get_CarteAutor()}"

    def printExtended(self) -> None:
        """Afiseaza toate atributele cartii."""
        print(self.get_CarteID(), self.get_CarteTitlu(), self.get_CarteAutor(), self.get_CarteDescriere())
