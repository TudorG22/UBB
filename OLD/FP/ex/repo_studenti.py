from student import Student


class RepoStudenti:
    """
    Repository responsabil cu stocarea obiectelor Student.

    Functionalitati:
        - adaugare studenti fara duplicate (dupa ID)
        - cautare dupa ID
        - stergere student
        - modificare nume student
    """

    def __init__(self):
        """
        Initializeaza repository-ul cu o lista goala de studenti.

        :return: None
        """
        self.__studenti = []

    def adauga(self, student):
        """
        Adauga un student in repository.

        :param student: obiect Student care trebuie adaugat
        :return: None

        :raises ValueError: daca exista deja un student cu acelasi ID
        """
        for s in self.__studenti:
            if s.get_id() == student.get_id():
                raise ValueError("Studentul este deja in lista.")

        self.__studenti.append(student)

    def get_all(self):
        """
        Returneaza lista tuturor studentilor din repository.

        :return: lista de obiecte Student (copie superficiala)
        """
        return list(self.__studenti)

    def cauta_dupa_id(self, id_student):
        """
        Cauta un student dupa ID.

        :param id_student: id-ul studentului cautat
        :return: obiectul Student daca exista, altfel None
        """
        for s in self.__studenti:
            if s.get_id() == id_student:
                return s
        return None

    def sterge(self, student_id):
        """
        Sterge studentul cu id-ul dat.

        :param student_id: id-ul studentului de sters
        :return: None

        :raises ValueError: daca studentul nu exista
        """
        for i in range(len(self.__studenti)):
            if self.__studenti[i].get_id() == student_id:
                del self.__studenti[i]
                return None

        raise ValueError("Studentul nu exista.")

    def modifica(self, student):
        """
        Modifica numele unui student existent.

        :param student: obiect Student cu id-ul deja existent, dar cu numele nou
        :return: None

        :raises ValueError: daca studentul cu acel ID nu exista
        """
        for s in self.__studenti:
            if s.get_id() == student.get_id():
                s.set_nume(student.get_nume())
                return None

        raise ValueError("Studentul nu exista.")

class FileRepoStudent(RepoStudenti):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()



    def __load_from_file(self):
        try:
            with open(self.__filename, "r", encoding="utf-8") as f:
                for line in f:
                    line = line.strip()
                    if not line:
                        continue
                    parts = line.split(";")
                    if len(parts) != 2:
                        raise ValueError("Fisier corupt: linie invalida")
                    sid_str, nume = parts[0].strip(), parts[1].strip()
                    super().adauga(Student(sid_str, nume))
        except FileNotFoundError:
            with open(self.__filename, "w", encoding="utf-8"):
                pass

    def __store_to_file(self):
        with open(self.__filename, "w", encoding="utf-8") as f:
            for st in super().get_all():
                f.write(f"{st.get_id()};{st.get_nume()}\n")

    def adauga(self, student):
        super().adauga(student)
        self.__store_to_file()

    def sterge(self, sid):
        super().sterge(sid)
        self.__store_to_file()

    def modifica(self, student):
        super().modifica(student)
        self.__store_to_file()

