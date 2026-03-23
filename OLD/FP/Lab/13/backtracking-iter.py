"""
Se dă o listă de numere întregi a1,...an generați toate sub-secvențele cu proprietatea că
suma numerelor este divizibul cu N dat.
"""

N = 2
secventa = list(i for i in range(-2, 3))
lungime = len(secventa)
solutii = []
memorie = [([], 0)]

def test_solutie(subsec):
    suma = sum(subsec)
    if suma % N == 0:
        return True 

def backtracking():
    while memorie:
        subsecv, i = memorie.pop()
        if i >= lungime:
            if test_solutie(subsecv):
                if not (subsecv in solutii):
                    solutii.append(subsecv)

        else:
            if test_solutie(subsecv):
                if not (subsecv in solutii):
                    solutii.append(subsecv)
            memorie.append((subsecv + [secventa[i]], i+1))
            memorie.append((subsecv, i+1))

backtracking()
print(solutii)
