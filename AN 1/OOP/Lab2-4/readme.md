# 3 Buget de familie

## Pentru compilare: pt Linux, ./build sau ./build-tests
## Rulare: ./run sau ./run-with-data pentru date preintroduse

Creati o aplicatie care permite gestiunea bugetului pentru o familie. Aplicatia trebuie sa
stocheze cheltuielile pe o luna. Fiecare cheltuiala are: zi (ziua in care s-a efectuat), suma,
tip (mancare, transport, telefon&internet, imbracaminte, altele).

Aplicatia permite:
a) Adaugarea de cheltuieli noi (cand familia cumpara ceva sau plateste o factura)
b) Modificarea unei cheltuieli existente (ziua, tipul, suma)
c) Stergere cheltuiala
d) Vizualizare lista de cheltuieli filtrata dupa o proprietate (suma, ziua, tipul)
e) Vizualizare lista de cheltuieli ordonata dupa suma sau tip (crescator/descrescator)

## Cerinte
- Aplicatie modulara in C
- Interfata utilizator de tip consola
- Datele introduse de utilizator trebuie validate
- Arhitectura stratificata
- Dezvoltare dirijata de teste
- Fiecare metoda trebuie specificata si testata
- Implementati vector dinamic pentru lucru cu liste
