from student import Student
import random
import string


class ServiceStudenti:
    """
    Service responsabil cu gestionarea studentilor:
    creare, validare, modificare, stergere și cautare.
    """

    def __init__(self, repo, validator):
        """
        Initializeaza un service pentru gestionarea studentilor.

        :param repo: repository-ul responsabil cu stocarea studentilor
        :param validator: validatorul utilizat pentru verificarea datelor studentilor
        :return: None
        """
        self.__repo = repo
        self.__validator = validator

    def adauga_student(self, sid, nume):
        """
        Adauga un student nou in sistem.

        :param sid: id-ul studentului (unic)
        :param nume: numele studentului
        :return: None

        :raises ValueError: daca datele sunt invalide
                            sau daca exista deja un student cu acelasi id
        """
        s = Student(sid, nume)
        self.__validator.valideaza(s)
        self.__repo.adauga(s)

    def get_all_studenti(self):
        """
        Returneaza lista tuturor studentilor din sistem.

        :return: lista de obiecte Student
        """
        return self.__repo.get_all()

    def cauta_dupa_id(self, sid):
        """
        Cauta un student dupa id.

        :param sid: id-ul studentului cautat
        :return: obiectul Student care are acest id

        :raises ValueError: daca studentul nu exista
        """
        return self.__repo.cauta_dupa_id(sid)

    def sterge_student(self, sid):
        """
        Sterge studentul cu id-ul dat.

        :param sid: id-ul studentului care trebuie sters
        :return: None

        :raises ValueError: daca studentul nu exista
        """
        self.__repo.sterge(sid)

    def modifica_student(self, sid, nume_nou):
        """
        Modifica numele unui student existent.

        :param sid: id-ul studentului care trebuie modificat
        :param nume_nou: noul nume al studentului
        :return: None

        :raises ValueError: daca datele sunt invalide
                            sau daca studentul nu exista
        """
        s = Student(sid, nume_nou)
        self.__validator.valideaza(s)
        self.__repo.modifica(s)

    def _gen_random_student_id(self):
        """
        Genereaza un ID numeric care nu exista deja in repo.
        """
        existente = {s.get_id() for s in self.__repo.get_all()}
        while True:
            candidate = str(random.randint(1, 9999))
            if candidate not in existente:
                return candidate

    def _gen_random_name(self, min_len=5, max_len=10):
        """
        Genereaza un nume random (string fara sens, dar valid).
        """
        lungime = random.randint(min_len, max_len)
        letters = string.ascii_lowercase
        nume = "".join(random.choice(letters) for _ in range(lungime))
        return nume.capitalize()

    def cauta_student(self, student_id):
        """
        cauta studentul cu id-ul dat
        :param student_id:
        :return:
        """
        return self.__repo.cauta_dupa_id(student_id)

    def genereaza_studenti_random(self, n):
        """
        Genereaza n studenti random si ii adauga in repository.

        :param n: numarul de studenti de generat (trebuie > 0)
        """
        if n <= 0:
            raise ValueError("n trebuie sa fie pozitiv.")

        for _ in range(n):
            sid = self._gen_random_student_id()
            nume = self._gen_random_name()
            s = Student(sid, nume)
            self.__validator.valideaza(s)
            self.__repo.adauga(s)
