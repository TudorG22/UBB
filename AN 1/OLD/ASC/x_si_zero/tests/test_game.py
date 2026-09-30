import unittest

from x_si_zero.domain.game import TicTacToeGame
from x_si_zero.domain.game_state import TicTacToeGameState


class TestTicTacToeGame(unittest.TestCase):
    def test_row_win(self):
        game = TicTacToeGame(1, [["X", "X", "X"], ["0", "-", "-"], ["-", "-", "-"]])
        self.assertEqual(game.state(), TicTacToeGameState.X_WON)

    def test_column_win(self):
        game = TicTacToeGame(2, [["0", "X", "-"], ["0", "X", "-"], ["0", "-", "-"]])
        self.assertEqual(game.state(), TicTacToeGameState.O_WON)

    def test_draw(self):
        board = [["X", "0", "X"], ["0", "X", "0"], ["0", "X", "0"]]
        game = TicTacToeGame(3, board)
        self.assertEqual(game.state(), TicTacToeGameState.DRAW)

    def test_in_progress(self):
        game = TicTacToeGame(4, [["-", "-", "-"], ["-", "X", "-"], ["-", "-", "-"]])
        self.assertEqual(game.state(), TicTacToeGameState.IN_PROGRESS)


if __name__ == "__main__":
    unittest.main()
