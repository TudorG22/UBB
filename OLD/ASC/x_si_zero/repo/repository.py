from pathlib import Path
from typing import List

from ..domain.game import TicTacToeGame


class TicTacToeRepository:
    """Stores games in memory and keeps them persisted on disk."""

    def __init__(self, file_path: str):
        self._file_path = Path(file_path)
        self._file_path.parent.mkdir(parents=True, exist_ok=True)
        if not self._file_path.exists():
            self._file_path.write_text("", encoding="utf-8")

    def _load(self) -> List[TicTacToeGame]:
        games: List[TicTacToeGame] = []
        content = self._file_path.read_text(encoding="utf-8").splitlines()
        for line in content:
            if not line.strip():
                continue
            parts = [part.strip() for part in line.split(",")]
            if len(parts) != 10:
                raise ValueError(f"Invalid line: {line}")
            game_id = int(parts[0])
            cells = [parts[i] for i in range(1, 10)]
            board = [cells[0:3], cells[3:6], cells[6:9]]
            games.append(TicTacToeGame(game_id, board))
        return games

    def _save(self, games: List[TicTacToeGame]) -> None:
        lines = []
        for game in games:
            flattened = [str(cell) for row in game.board for cell in row]
            lines.append(",".join([str(game.id), *flattened]))
        self._file_path.write_text("\n".join(lines), encoding="utf-8")

    def get_all(self) -> List[TicTacToeGame]:
        return self._load()

    def find_by_id(self, game_id: int) -> TicTacToeGame | None:
        for game in self._load():
            if game.id == game_id:
                return game
        return None

    def update(self, game: TicTacToeGame) -> None:
        games = self._load()
        for idx, existing in enumerate(games):
            if existing.id == game.id:
                games[idx] = game
                self._save(games)
                return
        raise ValueError(f"Game with id {game.id} not found")

    def add(self, game: TicTacToeGame) -> None:
        games = self._load()
        if any(g.id == game.id for g in games):
            raise ValueError(f"Game id {game.id} already exists")
        games.append(game)
        self._save(games)
