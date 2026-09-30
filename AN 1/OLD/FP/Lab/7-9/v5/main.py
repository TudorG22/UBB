from repo.carte_repo import CarteRepository
from repo.client_repo import ClientRepository
from service.library_service import LibraryService
from ui.console import ruleaza


if __name__ == "__main__":
    carti_repo = CarteRepository()
    clienti_repo = ClientRepository()
    service = LibraryService(carti_repo, clienti_repo)
    ruleaza(service)
