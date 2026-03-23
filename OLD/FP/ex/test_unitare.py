"""
Teste unitare pentru entitatile Student, Nota, Disciplina,
validatori, repository-uri si ServiceNote.
"""

from service_note import ServiceNote
from service_studenti import ServiceStudenti
from nota import Nota
from student import Student
from disciplina import Disciplina
from validator import ValidatorStudent, ValidatorNota
from repo_discipline import RepoDiscipline
from repo_note import RepoNote
from repo_studenti import RepoStudenti
import pytest


def test_student_creare_si_get():
    """
    Verifica faptul ca un Student este creat corect
    si ca get_id, get_nume returneaza valorile asteptate.
    """
    s = Student("1", "Ion")
    assert s.get_id() == "1"
    assert s.get_nume() == "Ion"


def test_validator_student():
    """
    Verifica validarea corecta a unui Student:
    - student valid NU arunca exceptie
    - studenti cu id sau nume invalide arunca ValueError.
    """
    v = ValidatorStudent()
    v.valideaza(Student("10", "Ana"))
    for sid, nume in [("", "Ana"), ("10", ""), (None, "x")]:
        try:
            v.valideaza(Student(sid, nume))
            assert False, "Trebuia ValueError"
        except ValueError:
            pass

def test_repo():
    """
    Verifica functionalitatile de baza ale RepoStudenti:
    adaugare, get_all si interdictia de duplicate.
    """
    repo = RepoStudenti()
    s1 = Student("1", "Ion")
    repo.adauga(s1)
    lista = repo.get_all()
    assert len(lista) == 1
    assert lista[0] == s1
    try:
        repo.adauga(Student("1", "AltNume"))
        assert False, "Trebuia ValueError pentru duplicat"
    except ValueError:
        pass


def test_creare_nota_valida():
    """
    Verifica constructia unei Note si accesul la atribute prin getter-ele ei.
    """
    n = Nota("1", "1", "1", 5)
    assert n.get_disciplina_id() == "1"
    assert n.get_student_id() == "1"
    assert n.get_id_nota() == "1"
    assert n.get_valoare() == 5


def test_note_egale_dupa_id():
    """
    Verifica faptul ca doua Note cu acelasi id sunt considerate egale.
    """
    n1 = Nota("1", "1", "1", 5)
    n2 = Nota("1", "4", "2", 5)
    assert n1 == n2


def test_str_nota():
    """
    Verifica reprezentarea textuala a unei Note
    (toate atributele apar in string).
    """
    n = Nota("1", "10", "20", 7)
    s = str(n)
    assert "1" in s
    assert "10" in s
    assert "20" in s
    assert "7" in s


def test_valoare_sub_1_arunca_eroare():
    """
    Verifica faptul ca o nota cu valoare < 1 este considerata invalida.
    """
    v = ValidatorNota()
    n = Nota("1", "10", "20", 0)
    try:
        v.valideaza(n)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "Valoare nota invalida."


def test_valoare_peste_10_arunca_eroare():
    """
    Verifica faptul ca o nota cu valoare > 10 este considerata invalida.
    """
    v = ValidatorNota()
    n = Nota("1", "10", "20", 11)
    try:
        v.valideaza(n)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "Valoare nota invalida."


def test_student_id_gol_arunca_eroare():
    """
    Verifica faptul ca lipsa id-ului de student la Nota este semnalata cu eroare.
    """
    v = ValidatorNota()
    n = Nota("1", "", "20", 5)
    try:
        v.valideaza(n)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "ID student invalid."


def test_disciplina_id_gol_arunca_eroare():
    """
    Verifica faptul ca lipsa id-ului de disciplina la Nota este semnalata cu eroare.
    """
    v = ValidatorNota()
    n = Nota("1", "10", "", 5)
    try:
        v.valideaza(n)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "ID disciplina invalid."


def test_adauga_o_nota_in_repo():
    """
    Verifica faptul ca RepoNote permite adaugarea unei singure note.
    """
    repo = RepoNote()
    n = Nota("1", "10", "20", 5)
    repo.adauga(n)
    all_note = repo.get_all()
    assert len(all_note) == 1
    assert all_note[0] == n


def test_repo_permite_mai_multe_note():
    """
    Verifica faptul ca RepoNote permite adaugarea mai multor note independente.
    """
    repo = RepoNote()
    n1 = Nota("1", "10", "20", 5)
    n2 = Nota("2", "10", "20", 8)
    repo.adauga(n1)
    repo.adauga(n2)

    all_note = repo.get_all()
    assert len(all_note) == 2
    assert n1 in all_note
    assert n2 in all_note


def test_sterge_nota_existenta():
    """
    Verifica stergerea corecta a unei note existente din RepoNote.
    """
    repo = RepoNote()
    n1 = Nota("1", "10", "20", 5)
    n2 = Nota("2", "10", "20", 8)
    repo.adauga(n1)
    repo.adauga(n2)

    repo.sterge("1")
    all_note = repo.get_all()

    assert len(all_note) == 1
    assert all_note[0] == n2


def test_stergere_nota_inexistenta_arunca_eroare():
    """
    Verifica faptul ca stergerea unei note inexistente arunca ValueError.
    """
    repo = RepoNote()
    try:
        repo.sterge("999")
        assert False, "Trebuia sa arunce ValueError"
    except ValueError as e:
        assert str(e) == "Nota inexistenta."


def test_get_all_returneaza_copie():
    """
    Verifica faptul ca RepoNote.get_all() returneaza o copie a listei interne.
    Modificarile asupra listei returnate nu afecteaza repository-ul.
    """
    repo = RepoNote()
    n = Nota("1", "10", "20", 5)
    repo.adauga(n)

    lista1 = repo.get_all()
    lista2 = repo.get_all()

    assert lista1 is not lista2

    lista1.clear()

    assert len(repo.get_all()) == 1


def test_adauga_nota_student_inexistent():
    """
    Verifica faptul ca ServiceNote nu permite adaugarea unei note
    pentru un student inexistent.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_disciplina = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_disciplina, validator)

    try:
        srv.adauga_nota("999", "10", 8)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "Student inexistent."


def test_adauga_nota_disciplina_inexistenta():
    """
    Verifica faptul ca ServiceNote nu permite adaugarea unei note
    la o disciplina inexistenta.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s = Student("1", "Ana")
    repo_studenti.adauga(s)

    try:
        srv.adauga_nota("1", "10", 8)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "Disciplina inexistenta."


def test_adauga_nota_valoare_invalida():
    """
    Verifica faptul ca ServiceNote/ValidatorNota resping o nota
    cu valoare invalida chiar daca studentul si disciplina exista.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    repo_studenti.adauga(Student("1", "Ana"))
    repo_discipline.adauga(Disciplina("10", "Mate", "Popescu"))

    try:
        srv.adauga_nota("1", "10", 0)
        assert False, "Trebuia ValueError"
    except ValueError as e:
        assert str(e) == "Valoare nota invalida."


def test_adauga_nota_corecta():
    """
    Verifica scenariul complet de adaugare a unei note valide prin ServiceNote.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    repo_studenti.adauga(Student("1", "Ana"))
    repo_discipline.adauga(Disciplina("10", "Mate", "Popescu"))

    srv.adauga_nota("1", "10", 8)

    all_note = repo_note.get_all()
    assert len(all_note) == 1
    assert all_note[0].get_student_id() == "1"
    assert all_note[0].get_disciplina_id() == "10"
    assert all_note[0].get_valoare() == 8


def test_get_all_note_returneaza_toti():
    """
    Verifica faptul ca ServiceNote.get_all_note() returneaza toate notele
    si nu expune direct lista interna din RepoNote.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_disciplina = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_disciplina, validator)

    n1 = Nota("1", "10", "20", 8)
    n2 = Nota("2", "11", "21", 9)
    repo_note.adauga(n1)
    repo_note.adauga(n2)

    lista = srv.get_all_note()
    assert len(lista) == 2
    assert n1 in lista
    assert n2 in lista
    assert lista is not repo_note.get_all()


def test_medii_student_la_disciplina_ordonate_corect():
    """
    Verifica calculul si ordonarea mediilor la o disciplina
    (descrescator dupa medie, apoi alfabetic dupa nume).
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s1 = Student("1", "Ana")
    s2 = Student("2", "Bogdan")
    s3 = Student("3", "Andrei")

    repo_studenti.adauga(s1)
    repo_studenti.adauga(s2)
    repo_studenti.adauga(s3)

    d1 = Disciplina("10", "Mate", "Popescu")
    repo_discipline.adauga(d1)

    srv.adauga_nota("1", "10", 10)
    srv.adauga_nota("1", "10", 8)
    srv.adauga_nota("2", "10", 9)
    srv.adauga_nota("3", "10", 7)

    rezultat = srv.medii_student_la_disciplina("10")

    assert len(rezultat) == 3

    st0, med0 = rezultat[0]
    st1, med1 = rezultat[1]
    st2, med2 = rezultat[2]

    assert st0.get_nume() == "Ana"
    assert med0 == 9.0

    assert st1.get_nume() == "Bogdan"
    assert med1 == 9.0

    assert st2.get_nume() == "Andrei"
    assert med2 == 7.0


def test_medie_generala_student_fara_note_returneaza_none():
    """
    Verifica faptul ca media generala a unui student fara note este None.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s1 = Student("1", "Ana")
    repo_studenti.adauga(s1)

    medie = srv.medie_generala_student("1")
    assert medie is None


def test_medie_generala_student_corecta():
    """
    Verifica calculul mediei generale pe toate disciplinele
    pentru un student cu note multiple.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s1 = Student("1", "Ana")
    repo_studenti.adauga(s1)

    d1 = Disciplina("10", "Mate", "Popescu")
    d2 = Disciplina("20", "Info", "Ionescu")
    repo_discipline.adauga(d1)
    repo_discipline.adauga(d2)

    srv.adauga_nota("1", "10", 10)
    srv.adauga_nota("1", "10", 7)
    srv.adauga_nota("1", "20", 9)

    medie = srv.medie_generala_student("1")
    assert medie == 8.67


def test_studenti_dupa_medie_globala_ordonare_corecta():
    """
    Verifica ordonarea studentilor dupa media globala:
    descrescator dupa medie, la egalitate alfabetic dupa nume.
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s1 = Student("1", "Ana")
    s2 = Student("2", "Bogdan")
    s3 = Student("3", "Carmen")
    repo_studenti.adauga(s1)
    repo_studenti.adauga(s2)
    repo_studenti.adauga(s3)

    d1 = Disciplina("10", "Mate", "Popescu")
    repo_discipline.adauga(d1)

    # Ana: 10, 8 -> 9.0
    srv.adauga_nota("1", "10", 10)
    srv.adauga_nota("1", "10", 8)

    # Bogdan: 9 -> 9.0
    srv.adauga_nota("2", "10", 9)

    # Carmen: 7 -> 7.0
    srv.adauga_nota("3", "10", 7)

    rezultat = srv.studenti_dupa_medie_globala()

    assert len(rezultat) == 3

    st0, med0 = rezultat[0]
    st1, med1 = rezultat[1]
    st2, med2 = rezultat[2]

    assert st0.get_nume() == "Ana"
    assert med0 == 9.0

    assert st1.get_nume() == "Bogdan"
    assert med1 == 9.0

    assert st2.get_nume() == "Carmen"
    assert med2 == 7.0


def test_studenti_dupa_medie_globala_top_20():
    """
    Verifica selectarea primilor 20% studenti
    dupa media globala (pe baza rezultatului ordonat).
    """
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()
    validator = ValidatorNota()
    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, validator)

    s1 = Student("1", "Ana")
    s2 = Student("2", "Bogdan")
    s3 = Student("3", "Carmen")
    s4 = Student("4", "Dan")
    s5 = Student("5", "Emil")
    repo_studenti.adauga(s1)
    repo_studenti.adauga(s2)
    repo_studenti.adauga(s3)
    repo_studenti.adauga(s4)
    repo_studenti.adauga(s5)

    d1 = Disciplina("10", "Mate", "Popescu")
    repo_discipline.adauga(d1)

    # Ana: 10 -> 10.0
    srv.adauga_nota("1", "10", 10)
    # Bogdan: 9 -> 9.0
    srv.adauga_nota("2", "10", 9)
    # Carmen: 8 -> 8.0
    srv.adauga_nota("3", "10", 8)
    # Dan: 7 -> 7.0
    srv.adauga_nota("4", "10", 7)
    # Emil: 6 -> 6.0
    srv.adauga_nota("5", "10", 6)

    rezultat = srv.studenti_dupa_medie_globala()  # toti, sortati

    import math
    k = max(1, math.ceil(0.2 * len(rezultat)))
    top = rezultat[:k]

    assert len(top) == 1
    st0, med0 = top[0]
    assert st0.get_nume() == "Ana"
    assert med0 == 10.0

def test_raport_discipline_dupa_medie():
    # repo-uri goale
    repo_note = RepoNote()
    repo_studenti = RepoStudenti()
    repo_discipline = RepoDiscipline()

    srv = ServiceNote(repo_note, repo_studenti, repo_discipline, ValidatorNota())

    # discipline
    d1 = Disciplina("1", "Mate", "ProfA")
    d2 = Disciplina("2", "Info", "ProfB")
    repo_discipline.adauga(d1)
    repo_discipline.adauga(d2)

    # note:
    # Mate -> 10, 8  => medie 9.0 (2 note)
    # Info -> 5      => medie 5.0 (1 nota)
    repo_note.adauga(Nota("1", "s1", "1", 10))
    repo_note.adauga(Nota("2", "s2", "1", 8))
    repo_note.adauga(Nota("3", "s3", "2", 5))

    rezultat = srv.discipline_dupa_medie()

    # verific ca sunt 2 discipline
    assert len(rezultat) == 2

    # verific ordinea DESCRESCATOARE dupa medie
    # Mate (9.0) inainte de Info (5.0)

    assert rezultat[0][0].get_id() == "1"   # Mate
    assert abs(rezultat[0][1] - 9.0) < 1e-6
    assert rezultat[0][2] == 2              # doua note

    assert rezultat[1][0].get_id() == "2"   # Info
    assert abs(rezultat[1][1] - 5.0) < 1e-6
    assert rezultat[1][2] == 1              # o nota


from student import Student
from repo_studenti import FileRepoStudent

def test_filerepo_student_store_then_reload(tmp_path):
    f = tmp_path / "studenti.txt"

    repo = FileRepoStudent(str(f))
    repo.adauga(Student("1", "Ion"))
    repo.adauga(Student("2", "Ana"))

    # Reincarcare din fisier
    repo2 = FileRepoStudent(str(f))
    s1 = repo2.cauta_dupa_id("1")
    s2 = repo2.cauta_dupa_id("2")

    assert s1 is not None and s1.get_nume() == "Ion"
    assert s2 is not None and s2.get_nume() == "Ana"
    assert len(repo2.get_all()) == 2


def test_filerepo_student_delete_then_reload(tmp_path):
    f = tmp_path / "studenti.txt"

    repo = FileRepoStudent(str(f))
    repo.adauga(Student("1", "Ion"))
    repo.adauga(Student("2", "Ana"))

    repo.sterge("1")

    repo2 = FileRepoStudent(str(f))
    assert repo2.cauta_dupa_id("1") is None
    assert repo2.cauta_dupa_id("2") is not None
    assert len(repo2.get_all()) == 1


def test_filerepo_student_corrupt_file_raises(tmp_path):
    f = tmp_path / "studenti.txt"

    f.write_text("1 Ion\n2;Ana\n", encoding="utf-8")

    with pytest.raises(ValueError):
        FileRepoStudent(str(f))

        #pt discipline si note este optionala testarea, subclasele sunt efectiv copypaste-uri la filerepo

from sortari import generic_sort

def test_quick_sort_basic():
    lst = [5, 1, 4, 2, 3]
    assert generic_sort(lst, algorithm="quick") == [1,2,3,4,5]
    assert lst == [5, 1, 4, 2, 3]  # nu modifica originalul

def test_gnome_sort_basic():
    lst = [3, 2, 2, 1]
    assert generic_sort(lst, algorithm="gnome") == [1,2,2,3]

def test_key_and_reverse():
    lst = ["bbb", "a", "cccc"]
    assert generic_sort(lst, key=len, reverse=True, algorithm="quick") == ["cccc","bbb","a"]

def test_cmp_custom():
    lst = [("Ion", 3), ("Ana", 1), ("Dan", 2)]
    cmp2 = lambda x, y: (x[1] > y[1]) - (x[1] < y[1])
    assert generic_sort(lst, cmp=cmp2, algorithm="gnome") == [("Ana",1), ("Dan",2), ("Ion",3)]

def test_quick_equals_gnome():
    lst = [9, 7, 8, 1, 3]
    assert generic_sort(lst, algorithm="quick") == generic_sort(lst, algorithm="gnome")
