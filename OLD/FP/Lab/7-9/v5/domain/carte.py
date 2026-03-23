class Carte:
    """
    Entitate carte: id, titlu, descriere, autor.
    """

    def __init__(self, id: int, titlu: str, descriere: str, autor: str) -> None:
        self.date = [id, titlu, descriere, autor]

    def get_id(self) -> int:
        return self.date[0]

    def get_titlu(self) -> str:
        return self.date[1]

    def get_descriere(self) -> str:
        return self.date[2]

    def get_autor(self) -> str:
        return self.date[3]

    def set_id(self, id: int) -> None:
        self.date[0] = id

    def set_titlu(self, titlu: str) -> None:
        self.date[1] = titlu

    def set_descriere(self, descriere: str) -> None:
        self.date[2] = descriere

    def set_autor(self, autor: str) -> None:
        self.date[3] = autor

    def __str__(self) -> str:
        return f"{self.get_id()}. '{self.get_titlu()}' scrisa de {self.get_autor()}"
