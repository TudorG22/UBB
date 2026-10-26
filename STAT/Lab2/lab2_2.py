from random import uniform

# patratul are colturi in (0, 0), (1, 0), (1, 1), (0, 1)
# cercul tangent laturilor are centrul in (0.5, 0.5) si raza 0.5

for n in [500, 1000, 2000]:
    puncte_in_cerc = 0

    for _ in range(n):
        x = uniform(0, 1)
        y = uniform(0, 1)

        if (x - 0.5) ** 2 + (y - 0.5) ** 2 <= 0.5 ** 2:
            puncte_in_cerc += 1

    frecventa_relativa = puncte_in_cerc / n
    print("N =", n, ", frecventa relativa =", frecventa_relativa)
