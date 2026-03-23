from Repo.costum_repo_file import CostumRepositoryFile
from Repo.inchiriere_repo import InchiriereRepository
from Validatori.costum_validator import CostumValidator
from Validatori.inchiriere_validator import InchiriereValidator
from Service.service import Service
from UI.ui import Console
from Teste.teste import ruleaza_teste


def main():
    """Punctul de intrare: ruleaza testele si porneste consola."""
    ruleaza_teste()
    costum_repo = CostumRepositoryFile("/home/dan/Documents/UBB/FP/Simulare/Repo/costume.txt")
    inchiriere_repo = InchiriereRepository()
    costum_validator = CostumValidator()
    inchiriere_validator = InchiriereValidator()

    srv = Service(costum_repo, inchiriere_repo, costum_validator, inchiriere_validator)

    consola = Console(srv)
    consola.run()


if __name__ == "__main__":
    main()
