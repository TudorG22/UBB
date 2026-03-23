# service_discipline.py
from disciplina import Disciplina
import random
import string

class ServiceDiscipline:
    """
    Orchestrator pentru entitatea Disciplina: construieste, valideaza si persista discipline.
    """

    def __init__(self, repo, validator):
        """
        Initializeaza un service pentru gestionarea disciplinelor.

        :param repo: repository-ul responsabil cu stocarea disciplinelor
        :param validator: validatorul utilizat pentru verificarea corectitudinii unei discipline
        :return: None
        """
        self.__repo = repo
        self.__validator = validator


    def adauga_disciplina(self, did, nume, profesor):
        """
        Adauga o noua disciplina in sistem.

        :param did: id-ul disciplinei (unic)
        :param nume: numele disciplinei
        :param profesor: numele profesorului asociat disciplinei
        :return: None

        :raises ValueError: daca datele sunt invalide sau disciplina exista deja
        """
        d = Disciplina(did, nume, profesor)
        self.__validator.valideaza(d)
        self.__repo.adauga(d)


    def modifica_disciplina(self, did, nume_nou, profesor_nou):
        """
        Modifica o disciplina existenta.

        :param did: id-ul disciplinei care trebuie modificata
        :param nume_nou: numele nou al disciplinei
        :param profesor_nou: profesorul nou al disciplinei
        :return: None

        :raises ValueError: daca datele noi sunt invalide sau disciplina nu exista
        """
        d = Disciplina(did, nume_nou, profesor_nou)
        self.__validator.valideaza(d)
        self.__repo.modifica(d)


    def sterge_disciplina(self, did):
        """
        Sterge disciplina cu id-ul dat.

        :param did: id-ul disciplinei care trebuie stearsa
        :return: None

        :raises ValueError: daca disciplina nu exista
        """
        self.__repo.sterge(did)


    def get_all_discipline(self):
        """
        Returneaza lista tuturor disciplinelor din sistem.

        :return: lista de obiecte Disciplina
        """
        return self.__repo.get_all()


    def cauta_dupa_id(self, did):
        """
        Cauta o disciplina dupa id.

        :param did: id-ul disciplinei cautate
        :return: obiectul Disciplina corespunzator id-ului dat

        :raises ValueError: daca disciplina nu exista
        """
        return self.__repo.cauta_dupa_id(did)

    def _gen_random_disciplina_id(self):
        existente = {d.get_id() for d in self.__repo.get_all()}
        while True:
            candidate = str(random.randint(1, 9999))
            if candidate not in existente:
                return candidate


    def cauta_disciplina(self, disciplina_id):
        """
        cauta disciplina dupa id-ul dat de la tastatura
        :param disciplina_id:
        :return:
        """
        return self.__repo.cauta_dupa_id(disciplina_id)

    def _gen_random_text(self, min_len=5, max_len=12):
        lungime = random.randint(min_len, max_len)
        letters = string.ascii_lowercase
        txt = "".join(random.choice(letters) for _ in range(lungime))
        return txt.capitalize()

    def genereaza_discipline_random(self, n):
        """
        Genereaza n discipline random si le adauga in repository.
        """
        if n <= 0:
            raise ValueError("n trebuie sa fie pozitiv.")

        for _ in range(n):
            did = self._gen_random_disciplina_id()
            nume = self._gen_random_text()
            profesor = self._gen_random_text()
            d = Disciplina(did, nume, profesor)
            self.__validator.valideaza(d)
            self.__repo.adauga(d)
