from enum import Enum, auto


class TicTacToeGameState(Enum):
    """Describes the status of a Tic Tac Toe game."""

    IN_PROGRESS = auto()
    X_WON = auto()
    O_WON = auto()
    DRAW = auto()
