import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from entities import *
from date_utils import *
from services import *

tranzactii.clear()
istoric.clear()

t = creeaza_tranzactie("01.01.2024", 100, "intrare")
assert get_data(t) == "01.01.2024"
assert get_suma(t) == 100
assert get_tip(t) == "intrare"
set_data(t, "02.01.2024"); assert get_data(t) == "02.01.2024"
set_suma(t, 200); assert get_suma(t) == 200
set_tip(t, "iesire"); assert get_tip(t) == "iesire"

assert an_bisect(2000)
assert not an_bisect(1900)
assert este_data("01.01.2024")
assert not este_data("32.01.2024")
assert este_dupa_data("02.01.2024", "01.01.2024")
assert este_inainte_data("01.01.2024", "02.01.2024")

adauga_tranzactie("01.01.2024", 100, "intrare")
adauga_tranzactie("02.01.2024", 50, "iesire")
assert len(tranzactii) == 2
assert get_data(tranzactii[0]) == "01.01.2024"

actualizare_tranzactie("01.01.2024", 200, "intrare")
assert tranzactii[0]["suma"] == 200

rez = tranzactii_peste_suma(60)
assert len(rez) == 1 and rez[0]["data"] == "01.01.2024"

sterge_tranz_data("02.01.2024")
assert len(tranzactii) == 1
undo()
assert len(tranzactii) == 2

assert suma_totala_tip("intrare") == 200
assert sold_la_data("02.01.2024") == 150

print("All basic tests passed.")
