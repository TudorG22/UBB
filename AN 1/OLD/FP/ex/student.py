class Student:
    """
    Entitate care reprezinta un student.

    Atribute:
        __data: lista de forma [id_student, nume_student]
    """

    def __init__(self, id : str, nume : str):
        """
        Creeaza un obiect de tip Student.

        :param id: id-ul studentului (unic)
        :param nume: numele studentului
        :return: None
        """
        self.__data = [id, nume]

    def get_id(self):
        """
        Returneaza id-ul studentului.

        :return: string/int – id-ul studentului
        """
        return self.__data[0]

    def get_nume(self):
        """
        Returneaza numele studentului.

        :return: string – numele studentului
        """
        return self.__data[1]

    def __eq__(self, other):
        """
        Verifica egalitatea dintre doi studenti.

        Doi studenti sunt considerati egali daca au acelasi id.

        :param other: obiectul cu care se compara
        :return: True daca id-urile coincid, False altfel
        """
        if not isinstance(other, Student):
            return False
        return self.__data[0] == other.__data[0]

    def __repr__(self):
        """
        Returneaza o reprezentare textuala a studentului,
        utila pentru debugging.

        :return: string de forma "Student(id, nume)"
        """
        return f"Student({self.__data[0]}, {self.__data[1]})"

    def set_nume(self, nume):
        """
        Actualizeaza numele studentului.

        :param nume: noul nume al studentului
        :return: None
        """
        self.__data[1] = nume
