"""
Se dă o listă de numere întregi a1,...an generați toate sub-secvențele cu proprietatea că
suma numerelor este divizibul cu N dat.
"""

N = 10
secventa = list(i for i in range(-2, 3))
lungime = len(secventa)
solutii = []

def test_solutie(subsec):
    suma = sum(subsec)
    if suma % N == 0:
        return True 

def backtracking(subsecv, i):
    if i >= lungime:
        if test_solutie(subsecv):
            if not (subsecv in solutii):
                solutii.append(subsecv)

    else:
        if test_solutie(subsecv):
            if not (subsecv in solutii):
                solutii.append(subsecv)
        backtracking(subsecv + [secventa[i]], i+1)
        backtracking(subsecv, i+1)

backtracking([], 0)
print(solutii)