# --- testare format data si comparari ---

def an_bisect(an: int) -> bool:
    """
    Determina daca un an este bisect.
    Returneaza True daca:
      - an % 400 == 0
      - an % 4 == 0 si an % 100 != 0
    Altfel False.
    """
    if an % 400 == 0:
        return True
    elif an % 100 == 0:
        return False
    elif an % 4 == 0:
        return True
    else:
        return False


def este_data(data: str) -> bool:
    """
    Verifica daca un str reprezinta o data valida in formatul 'zz.ll.aaaa'.
    Returneaza True daca data respecta:
      - toate partile sunt numerice
      - zi, luna, an au dimensiunile si valorile corecte
    """
    descompunere = data.split(".")
    if len(descompunere) != 3:
        return False

    # testam daca sunt numere
    test1 = True
    for elt in descompunere:
        if not elt.isdigit():
            test1 = False

    # testam daca e o data valida si in ordinea specificata zi-luna-an
    # luna
    test2 = len(descompunere[1]) == 2 and int(descompunere[1]) > 0 and int(descompunere[1]) < 13

    # anul
    test4 = len(descompunere[2]) == 4 and int(descompunere[2]) > 0

    # ziua
    test3 = False
    if test2 and test1:
        if int(descompunere[1]) in [1, 3, 5, 7, 8, 10, 12]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[0]) < 32
        elif int(descompunere[1]) in [4, 6, 7, 9, 11]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[0]) < 31
        else:
            if test4:
                if an_bisect(int(descompunere[2])):
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 30
                else:
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 29

    return (test1 and test2 and test3 and test4)


def este_dupa_data(data_testata: str, data_referinta: str) -> bool:
    """
    Returneaza True daca data_testata >= data_referinta.
    Se verifica in ordinea: an, luna, zi.
    """
    assert(type(data_testata) == type(data_referinta) == str)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int, data_testata.split(".")))
    descompunere_referinta = list(map(int, data_referinta.split(".")))

    if descompunere_test[2] > descompunere_referinta[2]:
        return True
    elif descompunere_test[2] < descompunere_referinta[2]:
        return False

    elif descompunere_test[1] > descompunere_referinta[1]:
        return True
    elif descompunere_test[1] < descompunere_referinta[1]:
        return False

    else:
        return descompunere_test[0] >= descompunere_referinta[0]


def este_inainte_data(data_testata: str, data_referinta: str) -> bool:
    """
    Returneaza True daca data_testata <= data_referinta.
    Se verifica in ordinea: an, luna, zi.
    """
    assert(type(data_testata) == type(data_referinta) == str)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int, data_testata.split(".")))
    descompunere_referinta = list(map(int, data_referinta.split(".")))

    if descompunere_test[2] < descompunere_referinta[2]:
        return True
    elif descompunere_test[2] > descompunere_referinta[2]:
        return False

    elif descompunere_test[1] < descompunere_referinta[1]:
        return True
    elif descompunere_test[1] > descompunere_referinta[1]:
        return False

    else:
        return descompunere_test[0] <= descompunere_referinta[0]
