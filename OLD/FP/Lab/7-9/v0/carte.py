class carte:
    def __init__(self, id, titlu, descriere, autor):
        self.id = id
        self.titlu = titlu
        self.descriere = descriere
        self.autor = autor

    def get_CarteID(self):
        return(self.id)

    def get_CarteTitlu(self):
        return(self.titlu)

    def get_CarteDescriere(self):
        return(self.descriere)

    def get_CarteAutor(self):
        return(self.autor)

    def set_CarteID(self, id):
        self.id = id 

    def set_CarteTitlu(self, titlu):
        self.titlu = titlu

    def set_CarteDescriere(self, descriere):
        self.descriere = descriere 

    def set_CarteAutor(self, autor):
        self.autor = autor

    def __str__(self):
        return f"{self.get_CarteID()}. '{self.get_CarteTitlu()}' scrisa de {self.get_CarteAutor()}"

    def printExtended(self):
        print(get_CarteID(), get_CarteTitlu(), get_CarteAutor(), get_CarteDescriere())