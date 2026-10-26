from random import randint
from matplotlib.pyplot import plot, grid, xticks, yticks, title, show

# numarul de aparitii al fiecarei sume la 3 zaruri
sum_counts1 = {total: 0 for total in range(3,19)}
sum_counts2 = {total: 0 for total in range(3,19)}


# jucator 1: 100000 de aruncari aleatoare
for _ in range(100000):
    total = randint(1, 6) + randint(1, 6) + randint(1, 6)
    sum_counts1[total] += 1

plot(sum_counts1.keys(),sum_counts1.values(), 'ro')
show()
print(sum_counts1)

# jucator 2: 100000 de aruncari aleatoare
for _ in range(100000):
    total = randint(1, 6) + randint(1, 6) + randint(1, 6)
    sum_counts2[total] += 1

plot(sum_counts2.keys(),sum_counts2.values(), 'bo')
show()
print(sum_counts2)
