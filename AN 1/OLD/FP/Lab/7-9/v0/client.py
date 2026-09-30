class client:
    def __init__(self, id, nume, cnp):
        self.id = id
        self.nume = nume
        self.cnp = cnp

    def get_ClientID(self):
        return(self.id)

    def get_ClientNume(self):
        return(self.nume)

    def get_ClientCNP(self):
        return(self.cnp)

    def set_ClientID(self, id):
        self.id = id

    def set_ClientNume(self, nume):
        self.nume = nume

    def set_ClientCNP(self, cnp):
        self.cnp = cnp

    def __str__(self):
        return f"{get_ClientID()} {get_ClientNume()} {get_ClientCNP()}"

