class carte:
    """
    Clasa carte. Pastreaza id, titlu, descriere, autor.
    """
    def __init__(self, id: int, titlu: str, descriere: str, autor: str) -> None:
        """Initializeaza o carte folosind id, titlu, descriere, autor."""
        self.id = id
        self.titlu = titlu
        self.descriere = descriere
        self.autor = autor

    def get_CarteID(self) -> int:
        """Returneaza id-ul cartii."""
        return(self.id)

    def get_CarteTitlu(self) -> str:
        """Returneaza titlul cartii."""
        return(self.titlu)

    def get_CarteDescriere(self) -> str:
        """Returneaza descrierea cartii."""
        return(self.descriere)

    def get_CarteAutor(self) -> str:
        """Returneaza autorul cartii."""
        return(self.autor)

    def set_CarteID(self, id: int) -> None:
        """Seteaza id-ul cartii."""
        self.id = id 

    def set_CarteTitlu(self, titlu: str) -> None:
        """Seteaza titlul cartii."""
        self.titlu = titlu

    def set_CarteDescriere(self, descriere: str) -> None:
        """Seteaza descrierea cartii."""
        self.descriere = descriere 

    def set_CarteAutor(self, autor: str) -> None:
        """Seteaza autorul cartii."""
        self.autor = autor

    def __str__(self) -> str:
        """Returneaza o reprezentare text a cartii."""
        return f"{self.get_CarteID()}. '{self.get_CarteTitlu()}' scrisa de {self.get_CarteAutor()}"

    def printExtended(self) -> None:
        """Afiseaza toate atributele cartii."""
        print(get_CarteID(), get_CarteTitlu(), get_CarteAutor(), get_CarteDescriere())
