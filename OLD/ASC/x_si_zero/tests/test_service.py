import os
import tempfile
import unittest

from x_si_zero.repo.repository import TicTacToeRepository
from x_si_zero.service.service import TicTacToeService


class TestService(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.NamedTemporaryFile(delete=False, mode="w", encoding="utf-8")
        self.tmp.write("1,X,0,-,-,-,-,-,-,-\n2,X,X,X,0,0,-,-,-,-")
        self.tmp.close()
        repo = TicTacToeRepository(self.tmp.name)
        self.service = TicTacToeService(repo)

    def tearDown(self):
        os.unlink(self.tmp.name)

    def test_list_unfinished(self):
        games = self.service.list_unfinished_games()
        self.assertEqual(len(games), 1)
        self.assertEqual(games[0].id, 1)

    def test_make_move_marks_correct_player(self):
        game, player = self.service.make_move(1, 0, 2)
        self.assertEqual(game.cell(0, 2), "X")
        self.assertEqual(player, "X")

    def test_cannot_move_in_finished_game(self):
        with self.assertRaises(ValueError):
            self.service.make_move(2, 1, 2)

    def test_cannot_overwrite_cell(self):
        with self.assertRaises(ValueError):
            self.service.make_move(1, 0, 0)


if __name__ == "__main__":
    unittest.main()
