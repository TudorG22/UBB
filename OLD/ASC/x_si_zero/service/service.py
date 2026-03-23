from ..domain.game import TicTacToeGame
from ..domain.game_state import TicTacToeGameState
from ..repo.repository import TicTacToeRepository


class TicTacToeService:
    """Business logic for Tic Tac Toe management."""

    def __init__(self, repository: TicTacToeRepository):
        self._repository = repository

    def list_unfinished_games(self) -> list[TicTacToeGame]:
        return [
            game
            for game in self._repository.get_all()
            if game.state() == TicTacToeGameState.IN_PROGRESS
        ]

    def next_player(self, game: TicTacToeGame) -> str:
        x_count, zero_count = game.counts()
        return "X" if x_count == zero_count else "0"

    def make_move(self, game_id: int, row: int, col: int) -> tuple[TicTacToeGame, str]:
        self._validate_position(row, col)
        game = self._repository.find_by_id(game_id)
        if not game:
            raise ValueError("Joc inexistent")
        if game.state() != TicTacToeGameState.IN_PROGRESS:
            raise ValueError("Jocul este deja terminat")
        if game.cell(row, col) != TicTacToeGame.EMPTY_CELL:
            raise ValueError("Casuta deja ocupata")

        player = self.next_player(game)
        game.set_cell(row, col, player)  # type: ignore[arg-type]
        self._repository.update(game)
        return game, player

    @staticmethod
    def _validate_position(row: int, col: int) -> None:
        if row not in range(3) or col not in range(3):
            raise ValueError("Pozitia trebuie sa fie intre 0 si 2")
