from random import sample
from math import factorial
from itertools import permutations

from math import perm, comb
from itertools import permutations, combinations

from itertools import combinations_with_replacement

####### 2
### a - permutari
#print(list(permutations("randomise")))

### b - numar permutari
#print(factorial(len("randomise")))

### c - permutare aleatorie
#print(sample("randomise", len("randomise")))


####### 3 
def aranjamente(cuvant, k, aleator=False, numar_total=False):
    if numar_total:
        return perm(len(cuvant), k)
    elif aleator:
        return sample(cuvant, k)
    else: 
        return list(permutations(cuvant, k))
    
def combinari(cuvant, k, aleator=False, numar_total=False):
    if numar_total:
        return comb(len(cuvant), k)
    elif aleator:
        return sample(cuvant, k)
    else:
        return list(combinations(cuvant, k))


####### 4
def inghetata():
    arome = ["A", "C", "F", "K", "M", "V", "Z"]
    result = ["".join(x) for x in combinations_with_replacement(arome, 3)]
    print(result)

inghetata()