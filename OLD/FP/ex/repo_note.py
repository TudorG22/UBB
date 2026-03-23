from nota import Nota
class RepoNote:
    """
    Repository responsabil cu stocarea obiectelor Nota.

    Functionalitati:
        - adaugare note
        - stergere note dupa id
        - obtinerea tuturor notelor
    """

    def __init__(self):
        """
        Initializeaza repository-ul cu o lista goala de note.

        :return: None
        """
        self.__note = []

    def adauga(self, nota):
        """
        Adauga o nota in repository.

        :param nota: obiect de tip Nota care trebuie adaugat
        :return: None
        """
        self.__note.append(nota)

    def sterge(self, id_nota):
        """
        Sterge nota cu id-ul dat din repository.

        :param id_nota: id-ul notei care trebuie stearsa
        :return: None

        :raises ValueError: daca nu exista o nota cu id-ul dat
        """
        for i, n in enumerate(self.__note):
            if n.get_id_nota() == id_nota:
                del self.__note[i]
                return
        raise ValueError("Nota inexistenta.")

    def get_all(self):
        """
        Returneaza toate notele din repository.

        :return: lista de obiecte Nota (copie superficiala)
        """
        return self.__note.copy()

class FileRepoNote(RepoNote):
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
                    if len(parts) != 4:
                        continue
                    nid = parts[0]
                    sid = parts[1]
                    did = parts[2]
                    val = parts[3]
                    nota = Nota(nid, sid, did, val)
                    super().adauga(nota)
        except FileNotFoundError:
            with open(self.__filename, 'w') as _:
                pass

    def __store_to_file(self):
        with open(self.__filename, 'w') as f:
            for nota in self.get_all():
                f.write(f"{nota.get_id_nota()};{nota.get_student_id()};{nota.get_disciplina_id()};{nota.get_valoare()}\n")

    def adauga(self, nota):
        super().adauga(nota)
        self.__store_to_file()

    def sterge(self, id_nota):
        super().sterge(id_nota)
        self.__store_to_file()

