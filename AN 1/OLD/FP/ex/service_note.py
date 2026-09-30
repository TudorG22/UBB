from nota import Nota
from sortari import generic_sort

import random

class ServiceNote:
    """
    Service care gestioneaza notele:
    valideaza, asociaza cu studenti si discipline si ofera statistici.
    """

    def __init__(self, repo_note, repo_studenti, repo_discipline, validator_nota):
        """
        Initializeaza un service pentru gestionarea notelor.

        :param repo_note: repository-ul responsabil cu stocarea notelor
        :param repo_studenti: repository-ul cu studentii existenti
        :param repo_discipline: repository-ul cu disciplinele existente
        :param validator_nota: validatorul utilizat pentru verificarea corectitudinii unei note
        :return: None
        """
        self.__repo_note = repo_note
        self.__repo_studenti = repo_studenti
        self.__repo_discipline = repo_discipline
        self.__validator_nota = validator_nota



    def adauga_nota(self, sid, did, valoare):
            """
            Adauga o nota pentru studentul si disciplina date.

            Ridica ValueError daca:
            - studentul nu exista
            - disciplina nu exista
            - valoarea notei este invalida
            """
            # verificare existenta student
            student = self.__repo_studenti.cauta_dupa_id(sid)
            if student is None:
                raise ValueError("Student inexistent.")

            # verificare existenta disciplina
            disciplina = self.__repo_discipline.cauta_dupa_id(did)
            if disciplina is None:
                raise ValueError("Disciplina inexistenta.")

            # conversie + validare nota
            val = int(valoare)
            nota = Nota(None, sid, did, val)
            self.__validator_nota.valideaza(nota)
            self.__repo_note.adauga(nota)

    def get_all_note(self):
        """
        Returneaza toate notele din sistem.

        :return: lista de obiecte Nota existente in repository
        """
        return self.__repo_note.get_all()

    def medii_student_la_disciplina(self, did):
        """
        Calculeaza mediile studentilor la o disciplina data.

        :param did: id-ul disciplinei pentru care se calculeaza mediile
        :return: o lista de tupluri (student, medie),
                 ordonata descrescator dupa medie si alfabetic dupa numele studentului
        """
        note = self.__repo_note.get_all()
        note_la_disciplina = [n for n in note if n.get_disciplina_id() == did]

        note_pe_student = {}  # sid -> [valori]
        for n in note_la_disciplina:
            sid = n.get_student_id()
            note_pe_student.setdefault(sid, []).append(n.get_valoare())

        studenti = self.__repo_studenti.get_all()
        dict_studenti = {s.get_id(): s for s in studenti}

        rezultat = []
        for sid, valori in note_pe_student.items():
            if sid not in dict_studenti:
                continue
            medie = round(sum(valori) / len(valori), 2)
            student = dict_studenti[sid]
            rezultat.append((student, medie))

        #rezultat.sort(key=lambda pair: (-pair[1], pair[0].get_nume()))

        #return rezultat
        #implementare lab12
        return generic_sort(
            rezultat,
            key=lambda pair: (-pair[1], pair[0].get_nume()),
            algorithm="quick"
        )

    def _suma_rec(self, lst, i=0):
        if i == len(lst):
            return 0            #recursiviTATE LAB12
        return lst[i] + self._suma_rec(lst, i + 1)

    def medie_generala_student(self, sid):
        """
        Calculeaza media generala a unui student pe toate disciplinele.

        :param sid: id-ul studentului pentru care se calculeaza media
        :return: media generala (float rotunjit la 2 zecimale),
                 sau None daca studentul nu are nicio nota
        """
        note = self.__repo_note.get_all()
        valori = [n.get_valoare() for n in note if n.get_student_id() == sid]

        if not valori:
            return None

        medie = self._suma_rec(valori) / len(valori)  #implementare recursivitate
        return round(medie, 2)

    def studenti_dupa_medie_globala(self):
        """
        Calculeaza media globala pentru toti studentii cu note
        si ii ordoneaza descrescator dupa medie.

        :return: o lista de tupluri (student, medie_globala),
                 ordonata descrescator dupa medie si alfabetic dupa nume
        """
        studenti = self.__repo_studenti.get_all()

        rezultate = []
        for s in studenti:
            sid = s.get_id()
            medie = self.medie_generala_student(sid)
            if medie is not None:
                rezultate.append((s, medie))

        if not rezultate:
            return []

        #rezultate.sort(key=lambda pair: (-pair[1], pair[0].get_nume()))
        #return rezultate
        #implementare lab12
        return generic_sort(
            rezultate,
            key=lambda pair: (-pair[1], pair[0].get_nume()),
            algorithm="gnome"
        )

    def _gaseste_disciplina_rec(self, discipline, did, i=0):
        if i == len(discipline):
            return None                     #A DOUA FUNCTIE RECURSIVA
        if discipline[i].get_id() == did:
            return discipline[i]
        return self._gaseste_disciplina_rec(discipline, did, i + 1)

    def discipline_dupa_medie(self):
        """
        returneaza o lista de tupluri (disciplina, medie, nr_note)
        ordonata descrescator dupa medie.
        :return:
        """
        note = self.__repo_note.get_all()
        if not note:
            return []
        note_pe_disciplina = {}
        for n in note:
            did = n.get_disciplina_id()
            valoare = n.get_valoare()
            if did not in note_pe_disciplina:
                note_pe_disciplina[did] = []
            note_pe_disciplina[did].append(valoare)

        discipline = self.__repo_discipline.get_all()

        rezultat = []
        for did, valori in note_pe_disciplina.items():
            disciplina_gasita = None
            #for d in discipline:
               # if d.get_id() == did:
                    #disciplina_gasita = d
                    #break
            disciplina_gasita = self._gaseste_disciplina_rec(discipline, did) #implementare recursivitate

            if disciplina_gasita is None:
                continue

            medie = sum(valori) / len(valori)
            nr_note = len(valori)
            rezultat.append((disciplina_gasita, medie, nr_note))

        #rezultat.sort(key=lambda elem: elem[1])
        #return rezultat
        #iar lab 12
        return generic_sort(
            rezultat,
            key=lambda elem: elem[1],
            reverse=True,
            algorithm="quick"
        )

    def studenti_si_note_la_disciplina(self, did):
        """
        Returneaza studentii si notele lor la o disciplina data.

        :param did: id-ul disciplinei pentru care se extrag notele
        :return: o lista de tupluri (student, lista_note),
                 unde lista_note contine notele la disciplina respectiva,
                 ordonate descrescator; lista este ordonata alfabetic
                 dupa numele studentului
        """
        note = self.__repo_note.get_all()
        note_la_disciplina = [n for n in note if n.get_disciplina_id() == did]

        # grupez note pe student_id
        note_pe_student = {}  # sid -> [valori]
        for n in note_la_disciplina:
            sid = n.get_student_id()
            note_pe_student.setdefault(sid, []).append(n.get_valoare())

        # dictionar sid -> Student
        studenti = self.__repo_studenti.get_all()
        dict_studenti = {s.get_id(): s for s in studenti}

        rezultat = []
        for sid, valori in note_pe_student.items():
            if sid not in dict_studenti:
                continue

            student = dict_studenti[sid]
            #valori_sortate = sorted(valori, reverse=True)
            #rezultat.append((student, valori_sortate))

        # sortez alfabetic dupa numele studentului
        #rezultat.sort(key=lambda pair: pair[0].get_nume())

        #return rezultat
            valori_sortate = generic_sort(valori, reverse=True, algorithm="gnome")
            rezultat.append((student, valori_sortate))

        return generic_sort(rezultat, key=lambda pair: pair[0].get_nume(), algorithm="quick")

    def get_note_dto(self):
        """
        Construieste obiecte DTO pentru afisarea notelor in UI.

        :return: o lista de obiecte NotaDTO,
                 fiecare continand (nume_student, nume_disciplina, valoare)
        """
        rezultat = []
        for nota in self.get_all_note():
            student = self.__repo_studenti.cauta_dupa_id(nota.get_student_id())
            disciplina = self.__repo_discipline.cauta_dupa_id(nota.get_disciplina_id())

            dto = NotaDTO(student.get_nume(), disciplina.get_nume(), nota.get_valoare())
            rezultat.append(dto)
        return rezultat

    def _gen_random_nota_id(self):
        existente = {n.get_id_nota() for n in self.__repo_note.get_all()}
        # ignoram None ca sa nu blocam logica existenta
        existente.discard(None)

        while True:
            candidate = str(random.randint(1, 999999))
            if candidate not in existente:
                return candidate

    def genereaza_note_random(self, n):
        """
        Genereaza n note random si le adauga in repository.

        Alege random student, disciplina si valoare intre 1 si 10.
        """
        if n <= 0:
            raise ValueError("n trebuie sa fie pozitiv.")

        studenti = self.__repo_studenti.get_all()
        discipline = self.__repo_discipline.get_all()

        if not studenti or not discipline:
            raise ValueError("Trebuie sa existe cel putin un student si o disciplina pentru a genera note.")

        for _ in range(n):
            student = random.choice(studenti)
            disciplina = random.choice(discipline)
            valoare = random.randint(1, 10)

            id_nota = self._gen_random_nota_id()
            nota = Nota(id_nota, student.get_id(), disciplina.get_id(), valoare)

            self.__validator_nota.valideaza(nota)
            self.__repo_note.adauga(nota)


class NotaDTO:
    """
    Obiect de transport de date pentru afisarea notelor:
    contine doar informatiile necesare pentru UI.
    """

    def __init__(self, student_nume, disciplina_nume, valoare):
        """
        Creeaza un DTO pentru o nota.

        :param student_nume: numele studentului
        :param disciplina_nume: numele disciplinei
        :param valoare: valoarea notei
        :return: None
        """
        self._student_nume = student_nume
        self._disciplina_nume = disciplina_nume
        self._valoare = valoare

    def __str__(self):
        """
        Formateaza DTO-ul ca string pentru afisare.

        :return: reprezentare text de forma "student | disciplina | valoare"
        """
        return f"{self._student_nume} | {self._disciplina_nume} | {self._valoare}"

    def get_student_nume(self):
        """
        :return: numele studentului
        """
        return self._student_nume

    def get_disciplina_nume(self):
        """
        :return: numele disciplinei
        """
        return self._disciplina_nume

    def get_valoare(self):
        """
        :return: valoarea notei
        """
        return self._valoare


