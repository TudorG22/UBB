from disciplina import Disciplina


class RepoDiscipline:
    """
    Repository responsabil cu stocarea obiectelor Disciplina.

    Functionalitati:
        - stocare discipline fara duplicate (dupa ID)
        - cautare dupa ID
        - adaugare / stergere / modificare discipline
        - asigurarea integritatii prin erori explicite
    """

    def __init__(self):
        """
        Initializeaza repository-ul cu o lista goala de discipline.

        :return: None
        """
        self.__discipline = []

    def get_all(self):
        """
        Returneaza toate disciplinele din repository.

        :return: lista de obiecte Disciplina (copie superficiala)
        """
        return list(self.__discipline)

    def cauta_dupa_id(self, id_disciplina):
        """
        Cauta o disciplina dupa ID.

        :param id_disciplina: id-ul disciplinei cautate
        :return: obiectul Disciplina daca exista, altfel None
        """
        for d in self.__discipline:
            if d.get_id() == id_disciplina:
                return d
        return None

    def adauga(self, disciplina: Disciplina):
        """
        Adauga o disciplina noua in repository.

        :param disciplina: obiectul Disciplina care trebuie adaugat
        :return: None

        :raises ValueError: daca exista deja o disciplina cu acelasi ID
        """
        if self.cauta_dupa_id(disciplina.get_id()) is not None:
            raise ValueError("Disciplina este deja in lista.")

        self.__discipline.append(disciplina)

    def sterge(self, id_disciplina):
        """
        Sterge disciplina cu ID-ul dat.

        :param id_disciplina: id-ul disciplinei care trebuie stearsa
        :return: None

        :raises ValueError: daca disciplina nu exista
        """
        for i in range(len(self.__discipline)):
            if self.__discipline[i].get_id() == id_disciplina:
                del self.__discipline[i]
                return

        raise ValueError("Disciplina nu exista.")

    def modifica(self, disciplina_noua: Disciplina):
        """
        Inlocuieste o disciplina existenta cu o disciplina noua
        (identificata prin acelasi ID).

        :param disciplina_noua: noul obiect Disciplina care trebuie salvat
        :return: None

        :raises ValueError: daca disciplina cu acelasi ID nu exista
        """
        for i in range(len(self.__discipline)):
            if self.__discipline[i].get_id() == disciplina_noua.get_id():
                self.__discipline[i] = disciplina_noua
                return

        raise ValueError("Disciplina nu exista.")

class FileRepoDiscipline(RepoDiscipline):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line == "":
                        continue
                    parts = line.split(';')
                    if len(parts) != 3:
                        continue
                    id_disciplina = parts[0]
                    nume_disciplina = parts[1]
                    nume_profesor = parts[2]
                    disciplina = Disciplina(id_disciplina, nume_disciplina, nume_profesor)
                    super().adauga(disciplina)
        except FileNotFoundError:
            with open(self.__filename, 'w') as _:
                pass

    def __store_to_file(self):
        with open(self.__filename, 'w') as f:
            for disciplina in self.get_all():
                f.write(f"{disciplina.get_id()};{disciplina.get_nume()};{disciplina.get_profesor()}\n")

    def adauga(self, disciplina):
        super().adauga(disciplina)
        self.__store_to_file()

    def modifica(self, disciplina_noua):
        super().modifica(disciplina_noua)
        self.__store_to_file()

    def sterge(self, did):
        super().sterge(did)
        self.__store_to_file()
