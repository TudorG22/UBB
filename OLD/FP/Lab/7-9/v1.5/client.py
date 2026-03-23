class client:
    """
    Clasa client. Pastreaza id, nume, cnp.
    """
    def __init__(self, id: int, nume: str, cnp: str) -> None:
        """Initializeaza un client folosind id, nume si cnp."""
        self.date = [id, nume, cnp]

    def get_ClientID(self) -> int:
        """Returneaza id-ul clientului."""
        return(self.date[0])

    def get_ClientNume(self) -> str:
        """Returneaza numele clientului."""
        return(self.date[1])

    def get_ClientCNP(self) -> str:
        """Returneaza cnp-ul clientului."""
        return(self.date[2])

    def set_ClientID(self, id: int) -> None:
        """Seteaza id-ul clientului."""
        self.date[0] = id

    def set_ClientNume(self, nume: str) -> None:
        """Seteaza numele clientului."""
        self.date[1] = nume

    def set_ClientCNP(self, cnp: str) -> None:
        """Seteaza cnp-ul clientului."""
        self.date[2] = cnp

    def __str__(self) -> str:
        """Returneaza o reprezentare text a clientului."""
        return f"{get_ClientID()} {get_ClientNume()} {get_ClientCNP()}"
