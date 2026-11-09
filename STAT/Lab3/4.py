from random import sample
from random import randint

def monteCarlo(v): # a)
    k = randint(1,100)
    w = sample(v, k)
    return max(w)

#print(monteCarlo(range(1,101)))


#b) estimatie cu 10 000 rulari:
results=[(1 if monteCarlo(range(1,101)) == 100 else 0) for _ in range(10000)]
estim=sum(results)/10000
print(estim)

#c) 
#pentru un k fix, probabilitatea ca 100 sa fie ales este k/100
#k este ales uniform din {1, ..., 100}:
#P(max(w) = 100) = (1/100) * sum(k/100), k=1,...,100
#                = (1/10000) * (100 * 101)/2
#                = 5050/10000
#                = 0.505 = 50.5%    