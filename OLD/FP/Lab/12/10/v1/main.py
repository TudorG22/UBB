from repo.carte_repo_file import CarteRepositoryFile
from repo.client_repo_file import ClientRepositoryFile
from repo.imprumut_repo_file import ImprumutRepositoryFile
from service.library_service import LibraryService
from ui.console import Console


if __name__ == "__main__":
    carti_repo = CarteRepositoryFile("/home/dan/Documents/UBB/FP/Lab/10/v1/repo/data/carti.txt")
    clienti_repo = ClientRepositoryFile("/home/dan/Documents/UBB/FP/Lab/10/v1/repo/data/clienti.txt")
    imprumut_repo = ImprumutRepositoryFile("/home/dan/Documents/UBB/FP/Lab/10/v1/repo/data/imprumuturi.txt", clienti_repo, carti_repo)
    service = LibraryService(carti_repo, clienti_repo, imprumut_repo)
    console = Console(service)
    console.ruleaza() # pentru consola
