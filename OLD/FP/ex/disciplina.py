class Disciplina:
    """
    Entitate care reprezinta o disciplina academica.

    Atribute:
        __id_disciplina: string – identificator unic al disciplinei
        __nume: string – denumirea disciplinei
        __profesor: string – numele profesorului titular
    """

    def __init__(self, id_disciplina, nume, profesor):
        """
        Creeaza un obiect de tip Disciplina.

        :param id_disciplina: id-ul disciplinei (unic)
        :param nume: numele disciplinei
        :param profesor: numele profesorului titular
        :return None
        """
        self.__id_disciplina = id_disciplina
        self.__nume = nume
        self.__profesor = profesor

    def get_id(self):
        """
        Returneaza id-ul disciplinei.

        :return: string – id-ul disciplinei
        """
        return self.__id_disciplina

    def get_nume(self):
        """
        Returneaza numele disciplinei.

        :return: string – numele disciplinei
        """
        return self.__nume

    def get_profesor(self):
        """
        Returneaza numele profesorului titular.

        :return: string – numele profesorului
        """
        return self.__profesor

    def set_nume(self, nume_nou):
        """
        Actualizeaza numele disciplinei.

        :param nume_nou: noul nume al disciplinei
        :return: None
        """
        self.__nume = nume_nou

    def set_profesor(self, profesor_nou):
        """
        Actualizeaza numele profesorului titular.

        :param profesor_nou: noul nume al profesorului
        :return: None
        """
        self.__profesor = profesor_nou

    def __eq__(self, other):
        """
        Verifica egalitatea dintre doua discipline.

        Doua discipline sunt egale daca au acelasi id.

        :param other: obiectul cu care se compara
        :return: True daca disciplinele au acelasi id, False altfel
        """
        if not isinstance(other, Disciplina):
            return False
        return self.__id_disciplina == other.__id_disciplina

    def __str__(self):
        """
        Returneaza o reprezentare textuala a disciplinei.

        :return: string de forma "Disciplina(id, nume, profesor)"
        """
        return f"Disciplina({self.__id_disciplina}, {self.__nume}, {self.__profesor})"
