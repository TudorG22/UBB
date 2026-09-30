import os
import tempfile
import unittest

from x_si_zero.domain.game import TicTacToeGame
from x_si_zero.repo.repository import TicTacToeRepository


class TestRepository(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.NamedTemporaryFile(delete=False, mode="w", encoding="utf-8")
        self.tmp.write("1,X,0,-,-,-,-,-,-,-\n2,-,-,-,-,-,-,-,-,-")
        self.tmp.close()
        self.repo = TicTacToeRepository(self.tmp.name)

    def tearDown(self):
        os.unlink(self.tmp.name)

    def test_load_games(self):
        games = self.repo.get_all()
        self.assertEqual(len(games), 2)
        self.assertEqual(games[0].id, 1)

    def test_update_game(self):
        game = self.repo.find_by_id(1)
        self.assertIsNotNone(game)
        assert game
        game.set_cell(0, 2, "X")  # type: ignore[arg-type]
        self.repo.update(game)
        updated = self.repo.find_by_id(1)
        assert updated
        self.assertEqual(updated.cell(0, 2), "X")

    def test_add_game(self):
        new_game = TicTacToeGame(3, [["-", "-", "-"], ["-", "-", "-"], ["-", "-", "-"]])
        self.repo.add(new_game)
        self.assertEqual(len(self.repo.get_all()), 3)


if __name__ == "__main__":
    unittest.main()
