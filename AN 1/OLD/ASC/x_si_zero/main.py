from pathlib import Path

from .repo.repository import TicTacToeRepository
from .service.service import TicTacToeService
from .ui.console import run_console


def main() -> None:
    data_path = Path(__file__).parent / "data" / "jocuri.txt"
    repository = TicTacToeRepository(str(data_path))
    service = TicTacToeService(repository)
    run_console(service)


if __name__ == "__main__":
    main()
