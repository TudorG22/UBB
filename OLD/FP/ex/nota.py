class Nota:
    """
    Entitate care reprezinta o nota acordata unui student la o disciplina.

    Atribute:
        __id_nota: string/int – identificator unic al notei
        __student_id: string/int – id-ul studentului caruia ii apartine nota
        __disciplina_id: string/int – id-ul disciplinei la care a fost acordata nota
        __valoare: int – valoarea notei
    """

    def __init__(self, id_nota, student_id, disciplina_id, valoare):
        """
        Creeaza un obiect de tip Nota.

        :param id_nota: id-ul notei (unic sau None, daca repo-ul genereaza id-uri)
        :param student_id: id-ul studentului
        :param disciplina_id: id-ul disciplinei
        :param valoare: valoarea notei (int)
        :return: None
        """
        self.__id_nota = id_nota
        self.__student_id = student_id
        self.__disciplina_id = disciplina_id
        self.__valoare = valoare

    def get_id_nota(self):
        """
        Returneaza id-ul notei.

        :return: string/int – id-ul notei
        """
        return self.__id_nota

    def get_student_id(self):
        """
        Returneaza id-ul studentului asociat notei.

        :return: string/int – id-ul studentului
        """
        return self.__student_id

    def get_disciplina_id(self):
        """
        Returneaza id-ul disciplinei la care a fost acordata nota.

        :return: string/int – id-ul disciplinei
        """
        return self.__disciplina_id

    def get_valoare(self):
        """
        Returneaza valoarea notei.

        :return: int – valoarea notei
        """
        return self.__valoare

    def __eq__(self, other):
        """
        Verifica egalitatea dintre doua note.

        Doua note sunt egale daca au acelasi id.

        :param other: obiectul cu care se compara
        :return: True daca id-urile coincid, False altfel
        """
        if not isinstance(other, Nota):
            return False
        return self.__id_nota == other.__id_nota

    def __str__(self):
        """
        Returneaza o reprezentare textuala a notei.

        :return: string de forma:
                 "Nota: id, Student: student_id, Disciplina: disciplina_id, Valoare: valoare"
        """
        return (
            f"Nota: {self.__id_nota}, "
            f"Student: {self.__student_id}, "
            f"Disciplina: {self.__disciplina_id}, "
            f"Valoare: {self.__valoare}"
        )
