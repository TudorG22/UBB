import math

class Consola:
    """
    Interfata de utilizator (UI) text pentru gestionarea studentilor,
    disciplinelor si notelor. Comunica exclusiv cu service-uri
    si nu contine logica aplicatiei.
    """

    def __init__(self, srv_studenti, srv_discipline, srv_note):
        """
        Initializeaza consola si maparea comenzilor disponibile.

        :param srv_studenti: service-ul pentru operatii cu studenti
        :param srv_discipline: service-ul pentru operatii cu discipline
        :param srv_note: service-ul pentru operatii cu note
        :return: None
        """
        self._srv_studenti = srv_studenti
        self._srv_discipline = srv_discipline
        self._srv_note = srv_note
        self._ruleaza = True

        self._comenzi = {
            "1": self._ui_adauga_student,
            "2": self._ui_listeaza_studenti,
            "3": self._ui_modifica_student,
            "4": self._ui_sterge_student,
            "5": self._ui_adauga_disciplina,
            "6": self._ui_listeaza_discipline,
            "7": self._ui_modifica_disciplina,
            "8": self._ui_sterge_disciplina,
            "9": self._ui_adauga_nota,
            "10": self._ui_listeaza_note,
            "11": self._ui_rapoarte,
            "12": self._ui_genereaza_studenti_random,
            "13": self._ui_genereaza_discipline_random,
            "14": self._ui_genereaza_note_random,
            "15": self._ui_cauta_student,
            "16": self._ui_cauta_disciplina,
            "x": self._ui_exit,
        }

    def run(self):
        """
        Porneste bucla principala a aplicatiei.
        Afiseaza meniul, citeste comenzile si delega executia catre metode UI.

        :return: None
        """
        while self._ruleaza:
            self._print_meniu()
            cmd = input("Comanda: ").strip().lower()
            act = self._comenzi.get(cmd)

            if not act:
                print("Comanda invalidă.")
                continue

            try:
                act()
            except ValueError as ve:
                print(f"Eroare: {ve}")

    def _print_meniu(self):
        """
        Afiseaza meniul principal al aplicatiei.

        :return: None
        """
        print("\n=== Catalog – V2 (sapt 8) ===")
        print("1) Adauga student      2) Listeaza studenti")
        print("3) Modifica student    4) Sterge student")
        print("5) Adauga disciplina   6) Listeaza discipline")
        print("7) Modifica disciplina 8) Sterge disciplina")
        print("9) Adauga nota        10) Listeaza note")
        print("11) Rapoarte (Sub-menu)")
        print("12. Genereaza studenti random")
        print("13. Genereaza discipline random")
        print("14. Genereaza note random")
        print("15. Cauta student")
        print("16. Cauta disciplina")
        print("x) Iesire")

    # ----------------- STUDENTI -----------------

    def _ui_adauga_student(self):
        """
        Citeste datele unui student si il adauga folosind service-ul.

        :return: None
        """
        sid = input("ID student: ").strip()
        nume = input("Nume: ").strip()
        self._srv_studenti.adauga_student(sid, nume)
        print("OK: student adăugat.")

    def _ui_listeaza_studenti(self):
        """
        Afiseaza toti studentii existenti.

        :return: None
        """
        studenti = self._srv_studenti.get_all_studenti()
        if not studenti:
            print("(niciun student)")
            return
        for s in studenti:
            print(s)

    def _ui_modifica_student(self):
        """
        Citeste id-ul si noul nume si modifica studentul corespunzator.

        :return: None
        """
        sid = input("ID student: ").strip()
        nume_nou = input("Nume nou: ").strip()
        self._srv_studenti.modifica_student(sid, nume_nou)
        print("OK: student modificat.")

    def _ui_sterge_student(self):
        """
        Sterge un student dupa ID.

        :return: None
        """
        sid = input("ID student: ").strip()
        self._srv_studenti.sterge_student(sid)
        print("OK: student șters.")
    def _ui_cauta_student(self):
        """
        Cauta studentul dupa ID-ul dat.
        :return:
        """
        sid = input("Introdu ID-ul studentului: ")
        student = self._srv_studenti.cauta_student(sid)
        print(student)

    # ----------------- DISCIPLINE -----------------

    def _ui_adauga_disciplina(self):
        """
        Citeste datele unei discipline si o adauga folosind service-ul.

        :return: None
        """
        did = input("ID disciplină: ").strip()
        nume = input("Nume: ").strip()
        prof = input("Profesor: ").strip()
        self._srv_discipline.adauga_disciplina(did, nume, prof)
        print("OK: disciplină adăugată.")

    def _ui_listeaza_discipline(self):
        """
        Afiseaza toate disciplinele.

        :return: None
        """
        discipline = self._srv_discipline.get_all_discipline()
        if not discipline:
            print("(nicio disciplină)")
            return
        for d in discipline:
            print(d)

    def _ui_cauta_disciplina(self):
        """
        Cauta disciplina dupa ID-ul dat.
        :return:
        """
        did = input("Introdu ID-ul studentului: ")
        disciplina = self._srv_discipline.cauta_disciplina(did)
        print(disciplina)


    def _ui_modifica_disciplina(self):
        """
        Citeste noile date si modifica disciplina cu ID-ul dat.

        :return: None
        """
        did = input("ID disciplină: ").strip()
        nume_nou = input("Nume nou: ").strip()
        prof_nou = input("Profesor nou: ").strip()
        self._srv_discipline.modifica_disciplina(did, nume_nou, prof_nou)
        print("OK: disciplină modificată.")

    def _ui_sterge_disciplina(self):
        """
        Sterge disciplina cu ID-ul furnizat.

        :return: None
        """
        did = input("ID disciplină: ").strip()
        self._srv_discipline.sterge_disciplina(did)
        print("OK: disciplină ștearsă.")

    # ----------------- NOTE -----------------

    def _ui_adauga_nota(self):
        """
        Citeste datele unei note si o adauga prin service.

        :return: None
        """
        sid = input("ID student: ").strip()
        did = input("ID disciplina: ").strip()
        valoare = input("Valoare nota (1-10): ").strip()
        self._srv_note.adauga_nota(sid, did, valoare)
        print("OK: nota adaugata.")

    def _ui_listeaza_note(self):
        """
        Afiseaza toate notele sub forma DTO (nume student, nume disciplina, valoare).

        :return: None
        """
        note_dto = self._srv_note.get_note_dto()

        if len(note_dto) == 0:
            print("Nu exista note.")
            return

        for n in note_dto:
            print(f"Student: {n.get_student_nume()} | "
                  f"Disciplina: {n.get_disciplina_nume()} | "
                  f"Valoare: {n.get_valoare()}")
    # ----------------- RANDOM -------------------
    def _ui_genereaza_studenti_random(self):
        try:
            n = int(input("Cate persoane (studenti) random vrei sa generez? "))
            self._srv_studenti.genereaza_studenti_random(n)
            print(f"Am generat {n} studenti random.")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _ui_genereaza_discipline_random(self):
        try:
            n = int(input("Cate discipline random vrei sa generez? "))
            self._srv_discipline.genereaza_discipline_random(n)
            print(f"Am generat {n} discipline random.")
        except ValueError as e:
            print(f"Eroare: {e}")

    def _ui_genereaza_note_random(self):
        try:
            n = int(input("Cate note random vrei sa generez? "))
            self._srv_note.genereaza_note_random(n)
            print(f"Am generat {n} note random.")
        except ValueError as e:
            print(f"Eroare: {e}")

    # ----------------- RAPOARTE -----------------

    def _ui_rapoarte(self):
        """
        Afiseaza meniul de rapoarte si delega catre metoda corespunzatoare.

        :return: None
        """
        print("\n=== Rapoarte ===")
        print("1) Medii la disciplina")
        print("2) Studenti si notele lor la disciplina")
        print("3) Top 20% studenti dupa media globala")
        print("4) Discipline dupa medie")

        opt = input("Optiune: ").strip()

        if opt == "1":
            self._ui_raport_medii_la_disciplina()
        elif opt == "2":
            self._ui_raport_studenti_note_la_disciplina()
        elif opt == "3":
            self._ui_raport_top20()
        elif opt == "4":
            self._ui_raport_discipline_dupa_medie()
        else:
            print("Optiune invalida.")

    def _ui_raport_discipline_dupa_medie(self):
        """
        Afiseaza disciplinele ordonate dupa media notelor (descrescator).
        :return: None
        """
        rezultat = self._srv_note.discipline_dupa_medie()

        if not rezultat:
            print("Nu exista note in sistem.")
            return

        print("\nDiscipline ordonate dupa media notelor, de la cea mai grea disciplina la cea mai usoara:")
        for disciplina, medie, nr_note in rezultat:
            print(
                f"{disciplina.get_nume()} (prof. {disciplina.get_profesor()}) -> "
                f"medie {medie:.2f} ({nr_note} note)"
            )

    def _ui_raport_medii_la_disciplina(self):
        """
        Afiseaza media fiecarui student la disciplina aleasa.

        :return: None
        """
        did = input("ID disciplina: ").strip()
        rezultat = self._srv_note.medii_student_la_disciplina(did)

        if not rezultat:
            print("Nu exista note pentru disciplina data.")
            return

        for student, medie in rezultat:
            print(f"{student.get_nume()} -> {medie}")

    def _ui_raport_studenti_note_la_disciplina(self):
        """
        Afiseaza studentii si notele lor la o disciplina aleasa.

        :return: None
        """
        did = input("ID disciplina: ").strip()
        rezultat = self._srv_note.studenti_si_note_la_disciplina(did)

        if not rezultat:
            print("Nu exista note la disciplina data.")
            return

        for student, note in rezultat:
            print(f"{student.get_nume()}: {note}")

    def _ui_raport_top20(self):
        """
        Afiseaza primii 20% dintre studenti dupa media generala.

        :return: None
        """
        rezultat = self._srv_note.studenti_dupa_medie_globala()

        if not rezultat:
            print("Niciun student cu note.")
            return

        print("\nTop 20% studenti dupa media globala:")
        for student, medie in rezultat:
            print(f"{student.get_nume()} -> {medie}")

    # ----------------- EXIT -----------------

    def _ui_exit(self):
        """
        Opreste aplicatia.

        :return: None
        """
        self._ruleaza = False
        print("La revedere.")
