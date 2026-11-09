from random import sample
from math import comb


def prob_cond(nr_sim):
    countA, countB = 0, 0
    for _ in range(nr_sim):
        bile_extrase = sample(['red', 'blue', 'green'], counts=[5, 3, 2], k=3)
        if 'red' in bile_extrase:
            countA += 1
            if len(set(bile_extrase)) == 1:
                countB += 1
    return countB / countA


prob_cond(5000)


# i) se estimeaza P(toate cele 3 bile sunt rosii | cel putin una este rosie).
# countA numara extragerile cu cel putin o bila rosie, iar countB pe cele cu toate cele 3 bile rosii

# Din 120 de extrageri posibile, 10 nu au bile rosii, deci raman 110.
# Dintre acestea, 10 au toate cele 3 bile rosii: P = 10/110 = 1/11.
prob_teoretica = comb(5, 3) / (comb(10, 3) - comb(5, 3))
print(prob_teoretica)
