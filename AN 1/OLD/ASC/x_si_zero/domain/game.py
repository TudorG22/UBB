from copy import deepcopy
from typing import List, Literal

from .game_state import TicTacToeGameState

CellValue = Literal["X", "0", "-"]


class TicTacToeGame:
    """Domain object that stores a single Tic Tac Toe board and its identifier."""

    BOARD_SIZE = 3
    EMPTY_CELL: CellValue = "-"

    def __init__(self, game_id: int, board: List[List[str]]):
        self.__id = game_id
        normalized = self.__normalize_board(board)
        self.__board: List[List[CellValue]] = normalized

    @staticmethod
    def __normalize_board(board: List[List[str]]) -> List[List[CellValue]]:
        if len(board) != TicTacToeGame.BOARD_SIZE:
            raise ValueError("Board must have 3 rows")
        normalized_rows: List[List[CellValue]] = []
        for row in board:
            if len(row) != TicTacToeGame.BOARD_SIZE:
                raise ValueError("Each row must have 3 columns")
            normalized_row: List[CellValue] = []
            for value in row:
                val = value.strip().upper()
                if val == "":
                    val = TicTacToeGame.EMPTY_CELL
                if val not in {"X", "0", TicTacToeGame.EMPTY_CELL}:
                    raise ValueError(f"Invalid cell value: {value}")
                normalized_row.append(val)  # type: ignore[arg-type]
            normalized_rows.append(normalized_row)
        return normalized_rows

    @property
    def id(self) -> int:
        return self.__id

    @property
    def board(self) -> List[List[CellValue]]:
        return deepcopy(self.__board)

    def cell(self, row: int, col: int) -> CellValue:
        return self.__board[row][col]

    def set_cell(self, row: int, col: int, value: CellValue) -> None:
        self.__board[row][col] = value

    def state(self) -> TicTacToeGameState:
        winner = self.__winner()
        if winner == "X":
            return TicTacToeGameState.X_WON
        if winner == "0":
            return TicTacToeGameState.O_WON
        if any(TicTacToeGame.EMPTY_CELL in row for row in self.__board):
            return TicTacToeGameState.IN_PROGRESS
        return TicTacToeGameState.DRAW

    def counts(self) -> tuple[int, int]:
        x_count = sum(cell == "X" for row in self.__board for cell in row)
        zero_count = sum(cell == "0" for row in self.__board for cell in row)
        return x_count, zero_count

    def __winner(self) -> str | None:
        lines = []
        lines.extend(self.__board)
        lines.extend([[self.__board[r][c] for r in range(3)] for c in range(3)])
        lines.append([self.__board[i][i] for i in range(3)])
        lines.append([self.__board[i][2 - i] for i in range(3)])
        for line in lines:
            if line[0] != TicTacToeGame.EMPTY_CELL and line.count(line[0]) == 3:
                return line[0]
        return None

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, TicTacToeGame):
            return False
        return self.__id == other.__id and self.__board == other.__board

    def __repr__(self) -> str:
        return f"TicTacToeGame(id={self.__id}, board={self.__board!r})"

    def __str__(self) -> str:
        rows = [" ".join(row) for row in self.__board]
        return f"Joc #{self.__id}\n" + "\n".join(rows)
