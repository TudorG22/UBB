class Client:
    """
    Entitate client: id, nume, cnp.
    """

    def __init__(self, id: int, nume: str, cnp: str) -> None:
        self.date = [id, nume, cnp]

    def get_id(self) -> int:
        return self.date[0]

    def get_nume(self) -> str:
        return self.date[1]

    def get_cnp(self) -> str:
        return self.date[2]

    def set_id(self, id: int) -> None:
        self.date[0] = id

    def set_nume(self, nume: str) -> None:
        self.date[1] = nume

    def set_cnp(self, cnp: str) -> None:
        self.date[2] = cnp

    def __str__(self) -> str:
        return f"{self.get_id()} {self.get_nume()} {self.get_cnp()}"
