from student import Student


class ValidatorStudent:
    """
    Validator responsabil cu verificarea corectitudinii obiectelor Student.
    """

    def valideaza(self, student):
        """
        Valideaza un obiect de tip Student.

        :param student: obiectul Student care trebuie validat
        :return: None

        :raises ValueError:
            - daca id-ul este None sau string gol
            - daca numele este None sau string gol
            - daca obiectul nu este de tip Student
        """
        if not isinstance(student, Student):
            raise ValueError("Studentul nu este valid.")

        id_student = student.get_id()
        if id_student is None or id_student.strip() == "":
            raise ValueError("Id student nu este valid.")

        nume_student = student.get_nume()
        if nume_student is None or nume_student.strip() == "":
            raise ValueError("Nume student nu este valid.")
from disciplina import Disciplina

class ValidatorDisciplina:
    """
    Validator responsabil cu verificarea corectitudinii obiectelor Disciplina.
    """

    def valideaza(self, disciplina):
        """
        Valideaza o instanta de tip Disciplina.

        :param disciplina: obiectul Disciplina care trebuie validat
        :return: None

        :raises ValueError:
            - daca obiectul nu este Disciplina
            - daca id-ul este None sau gol
            - daca numele este None sau gol
            - daca profesorul este None sau gol
        """
        if not isinstance(disciplina, Disciplina):
            raise ValueError("Obiectul nu este de tip Disciplina.")

        erori = []

        if disciplina.get_id() is None or disciplina.get_id().strip() == "":
            erori.append("ID invalid.")
        if disciplina.get_nume() is None or disciplina.get_nume().strip() == "":
            erori.append("Nume disciplina invalid.")
        if disciplina.get_profesor() is None or disciplina.get_profesor().strip() == "":
            erori.append("Profesor invalid.")

        if len(erori) > 0:
            raise ValueError(" ".join(erori))

class ValidatorNota:
    """
    Validator responsabil cu verificarea corectitudinii obiectelor Nota.
    """

    def valideaza(self, nota):
        """
        Valideaza o instanta de tip Nota.

        :param nota: obiectul Nota care trebuie validat
        :return: None

        :raises ValueError:
            - daca id-ul studentului este None sau gol
            - daca id-ul disciplinei este None sau gol
            - daca valoarea notei nu este intre 1 si 10 (inclusiv)
        """
        erori = []

        if nota.get_student_id() is None or nota.get_student_id().strip() == "":
            erori.append("ID student invalid.")

        if nota.get_disciplina_id() is None or nota.get_disciplina_id().strip() == "":
            erori.append("ID disciplina invalid.")

        if nota.get_valoare() is None or nota.get_valoare() < 1 or nota.get_valoare() > 10:
            erori.append("Valoare nota invalida.")

        if len(erori) > 0:
            raise ValueError("\n".join(erori))
