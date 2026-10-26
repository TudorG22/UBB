from random import uniform
from math import pi
from matplotlib.pyplot import subplots, show

# patratul are colturi in (0, 0), (1, 0), (1, 1), (0, 1)
# cercul tangent laturilor are centrul in (0.5, 0.5) si raza 0.5

# spune daca triunghiul cu laturile la patrat a, b, c este ascutit sau obtuz
def tip_triunghi(a, b, c):
    latura_maxima = max(a, b, c)

    if latura_maxima < a + b + c - latura_maxima:
        return "ascutit"
    if latura_maxima > a + b + c - latura_maxima:
        return "obtuz"
    return "dreptunghic"


# a)
for n in [2000]:
    puncte_in_cerc = 0
    mai_aproape_de_centru_decat_de_varfuri = 0
    mai_aproape_de_centru_decat_de_latura_jos = 0
    doua_ascutite_doua_obtuze = 0

    puncte_i = []
    puncte_ii = []
    puncte_iii = []
    puncte_iv = []

    for _ in range(n):
        x = uniform(0, 1)
        y = uniform(0, 1)

        # i) punctul este in cerc
        if (x - 0.5) ** 2 + (y - 0.5) ** 2 <= 0.5 ** 2:
            puncte_in_cerc += 1
            puncte_i.append((x, y))

        # ii) punctul este mai aproape de centru decat de toate varfurile
        if (x + y > 0.5 and x + y < 1.5 and
                x - y < 0.5 and y - x < 0.5):
            mai_aproape_de_centru_decat_de_varfuri += 1
            puncte_ii.append((x, y))

        # iii) distanta pana la latura de jos este y
        distanta_centru = (x - 0.5) ** 2 + (y - 0.5) ** 2
        if distanta_centru < y ** 2:
            mai_aproape_de_centru_decat_de_latura_jos += 1
            puncte_iii.append((x, y))

        # iv) cele patru triunghiuri formate cu laturile patratului
        distanta_stanga_jos = x ** 2 + y ** 2
        distanta_dreapta_jos = (x - 1) ** 2 + y ** 2
        distanta_dreapta_sus = (x - 1) ** 2 + (y - 1) ** 2
        distanta_stanga_sus = x ** 2 + (y - 1) ** 2

        triunghiuri = [
            tip_triunghi(distanta_stanga_jos, distanta_dreapta_jos, 1),
            tip_triunghi(distanta_dreapta_jos, distanta_dreapta_sus, 1),
            tip_triunghi(distanta_dreapta_sus, distanta_stanga_sus, 1),
            tip_triunghi(distanta_stanga_sus, distanta_stanga_jos, 1)
        ]

        if triunghiuri.count("ascutit") == 2 and triunghiuri.count("obtuz") == 2:
            doua_ascutite_doua_obtuze += 1
            puncte_iv.append((x, y))

    print("N =", n)
    print("i)  ", puncte_in_cerc / n)
    print("probabilitatea teoretica i) =", pi / 4)
    print("ii) ", mai_aproape_de_centru_decat_de_varfuri / n)
    print("probabilitatea teoretica ii) =", 1 / 2)
    print("iii)", mai_aproape_de_centru_decat_de_latura_jos / n)
    print("probabilitatea teoretica iii) =", 2 / 3)
    print("iv) ", doua_ascutite_doua_obtuze / n)
    print("probabilitatea teoretica iv) =", pi / 2 - 1)
    print()

    # b)
    fig, axe = subplots(2, 2)

    for punct in puncte_i:
        axe[0][0].plot(punct[0], punct[1], "ro")
    axe[0][0].plot([0, 1, 1, 0, 0], [0, 0, 1, 1, 0], "b-")
    axe[0][0].set_title("i)")
    axe[0][0].set_aspect("equal")

    for punct in puncte_ii:
        axe[0][1].plot(punct[0], punct[1], "ro")
    axe[0][1].plot([0, 1, 1, 0, 0], [0, 0, 1, 1, 0], "b-")
    axe[0][1].set_title("ii)")
    axe[0][1].set_aspect("equal")

    for punct in puncte_iii:
        axe[1][0].plot(punct[0], punct[1], "ro")
    axe[1][0].plot([0, 1, 1, 0, 0], [0, 0, 1, 1, 0], "b-")
    axe[1][0].set_title("iii)")
    axe[1][0].set_aspect("equal")

    for punct in puncte_iv:
        axe[1][1].plot(punct[0], punct[1], "ro")
    axe[1][1].plot([0, 1, 1, 0, 0], [0, 0, 1, 1, 0], "b-")
    axe[1][1].set_title("iv)")
    axe[1][1].set_aspect("equal")


show()
