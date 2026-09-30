from ..domain.game_state import TicTacToeGameState
from ..service.service import TicTacToeService


def _format_board(game) -> str:
    lines = []
    for row in game.board:
        lines.append(" | ".join(row))
    return f"Joc #{game.id}\n" + "\n---------\n".join(lines)


def _print_status(game) -> None:
    state = game.state()
    if state == TicTacToeGameState.X_WON:
        print("A castigat jucatorul X.")
    elif state == TicTacToeGameState.O_WON:
        print("A castigat jucatorul 0.")
    elif state == TicTacToeGameState.DRAW:
        print("Remiza.")
    else:
        print("Joc in desfasurare.")


def show_unfinished(service: TicTacToeService) -> None:
    games = service.list_unfinished_games()
    if not games:
        print("Nu exista jocuri neterminate.")
        return
    for game in games:
        print(_format_board(game))
        print()


def play_move(service: TicTacToeService) -> None:
    try:
        game_id = int(input("Numarul jocului: "))
        row = int(input("Linia (0-2): "))
        col = int(input("Coloana (0-2): "))
        game, player = service.make_move(game_id, row, col)
        print(f"Mutare reusita pentru jucatorul {player}.")
        print(_format_board(game))
        _print_status(game)
    except ValueError as exc:
        print("Eroare:", exc)


def run_console(service: TicTacToeService) -> None:
    commands = {
        "1": show_unfinished,
        "2": play_move,
    }
    while True:
        print("1. Afisare jocuri neterminate")
        print("2. Marcheaza o casuta")
        print("0. Iesire")
        cmd = input(">> ").strip()
        if cmd == "0":
            break
        action = commands.get(cmd)
        if not action:
            print("Comanda invalida.")
            continue
        action(service)
