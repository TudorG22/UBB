from validator import ValidatorStudent, ValidatorDisciplina, ValidatorNota
from repo_note import RepoNote, FileRepoNote
from repo_studenti import RepoStudenti, FileRepoStudent
from repo_discipline import RepoDiscipline, FileRepoDiscipline
from service_studenti import ServiceStudenti
from service_discipline import ServiceDiscipline
from service_note import ServiceNote
from ui import Consola


def main():
    """
    Punctul de intrare al aplicatiei.

    Initializeaza:
        - validatorii (pentru studenti, discipline, note)
        - repository-urile (in-memory)
        - service-urile (care contin logica aplicatiei)
        - interfata de utilizator (UI)

    Porneste apoi bucla aplicatiei prin metoda ui.run().

    :return: None
    """
    # Validatori
    v_stud = ValidatorStudent()
    v_disc = ValidatorDisciplina()
    v_note = ValidatorNota()

    # Repository-uri
    r_stud = FileRepoStudent("studenti.txt")
    r_disc = FileRepoDiscipline("discipline.txt")
    r_note = FileRepoNote("note.txt")

    # Service-uri
    s_stud = ServiceStudenti(r_stud, v_stud)
    s_disc = ServiceDiscipline(r_disc, v_disc)
    s_note = ServiceNote(r_note, r_stud, r_disc, v_note)

    # UI
    ui = Consola(s_stud, s_disc, s_note)
    ui.run()


if __name__ == "__main__":
    main()
