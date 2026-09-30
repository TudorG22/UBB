# 4 - Cont bancar

## Enunt
Se cere realizarea unei aplicatii care gestioneaza un cont bancar.  
Fiecare tranzactie este caracterizata de **data (zz.ll.aaaa)**, **suma (numar intreg)** si **tipul** tranzactiei (`intrare` sau `iesire`).  
Aplicatia permite adaugarea, actualizarea, stergerea, cautarea si raportarea tranzactiilor, precum si afisarea listei si a soldului curent.

## Cerinte generale
- Se va utiliza procesul de **dezvoltare incrementala bazata pe functionalitati** si metoda **TDD (Test Driven Development)**.  
- Aplicatia se dezvolta in mai multe iteratii.  
- Toate functiile non-UI trebuie sa aiba specificatii clare (docstrings) si teste bazate pe `assert`.  
- Interfata cu utilizatorul (UI) trebuie separata de logica aplicatiei.  
- Toate operatiile logice (filtrare, cautare, raportare) sunt implementate in functii dedicate si apelate din UI.

---

## Lista de functionalitati (implementate)

### 1. Adaugare si actualizare tranzactii
- Adauga o tranzactie cu data, suma si tip (`intrare` sau `iesire`).
- Normalizeaza automat semnul sumei in functie de tip:
  - `intrare` → suma pozitiva  
  - `iesire` → suma negativa
- Actualizeaza o tranzactie existenta identificata dupa data.

### 2. Stergere tranzactii
- Sterge toate tranzactiile de la o data data.
- Sterge toate tranzactiile dintr-o perioada [data_inceput, data_final].
- Sterge toate tranzactiile de un anumit tip (`intrare` sau `iesire`).

### 3. Cautare si filtrare
Functiile de cautare returneaza liste de tranzactii care respecta anumite conditii:
- `tranzactii_peste_suma(suma)` → toate tranzactiile cu suma > valoarea data.
- `tranzactii_inainte_de_data_si_peste_suma(data, suma)` → toate tranzactiile efectuate **inainte de o data** si cu suma mai mare decat valoarea data.
- `tranzactii_de_tip(tip)` → toate tranzactiile de un anumit tip (`intrare` sau `iesire`).

### 4. Rapoarte si statistici
Functiile de raportare realizeaza calcule pe baza tranzactiilor existente:
- `suma_totala_tip(tip)` → calculeaza suma totala pentru tranzactiile de un anumit tip.
- `sold_la_data(data)` → determina soldul contului pana la o anumita data (inclusiv).
- `tranzactii_tip_ordonate_dupa_suma(tip, crescator=True)` → returneaza tranzactiile de un anumit tip ordonate dupa suma (crescator/descrescator).

### 5. Afisari si raportare curenta
- Listeaza toate tranzactiile curente.
- Afiseaza soldul contului calculat dupa toate tranzactiile existente:
  - pentru `intrare` → se aduna suma
  - pentru `iesire` → se scade suma

---

## Plan de iteratii

### Iteratia 1
- Implementare adaugare tranzactie (`adauga_tranzactie`).
- Implementare actualizare tranzactie (`actualizare_tranzactie`).
- Implementare functiile de validare a datelor (`este_data`, `an_bisect`).
- Scriere teste simple cu `assert` pentru functiile de baza.
- Adaugare functionalitati de stergere (`sterge_tranz_data`, `sterge_tranz_perioada`, `sterge_tranz_tip`).
- Implementare calcul de sold curent.
- Teste manuale prin consola.

### Iteratia 2
- Implementare functii de cautare:
  - `tranzactii_peste_suma`
  - `tranzactii_inainte_de_data_si_peste_suma`
  - `tranzactii_de_tip`
- Implementare functii de raportare:
  - `suma_totala_tip`
  - `sold_la_data`
  - `tranzactii_tip_ordonate_dupa_suma`
- Adaugare optiuni noi in meniu

### Iteratia 3 
- Functie undo
- Refactorizare modulara
- Testare mult mai elaborata

---

## Scenarii de rulare

## Scenarii de rulare

| utilizator | program                                                   | descriere                                                    |
| ----------- | --------------------------------------------------------- | ------------------------------------------------------------|
| 1           | "Data (zz.ll.aaaa):"                                     | se cere data tranzactiei                                     |
| 01.12.2024  |                                                           | utilizatorul introduce data tranzactiei                     |
|             | "Suma (int):"                                            | se cere suma tranzactiei                                     |
| 1000        |                                                           | utilizatorul introduce suma                                 |
|             | "Tip (intrare/iesire):"                                  | se cere tipul tranzactiei                                    |
| intrare     |                                                           | utilizatorul introduce tipul                                |
|             | "Tranzactie adaugata."                                   | se confirma adaugarea tranzactiei                            |
| 1           | "Data (zz.ll.aaaa):"                                     | se cere data pentru o noua tranzactie                        |
| 02.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Suma (int):"                                            | se cere suma                                                 |
| 500         |                                                           | utilizatorul introduce suma                                 |
|             | "Tip (intrare/iesire):"                                  | se cere tipul                                                |
| iesire      |                                                           | utilizatorul introduce tipul                                |
|             | "Tranzactie adaugata."                                   | se confirma adaugarea                                        |
| 2           | "Data tranzactiei de actualizat:"                        | se cere data pentru actualizare                              |
| 01.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Suma noua (int):"                                       | se cere suma noua                                            |
| 1200        |                                                           | utilizatorul introduce suma noua                            |
|             | "Tip nou (intrare/iesire):"                              | se cere tipul nou                                            |
| intrare     |                                                           | utilizatorul introduce tipul nou                            |
|             | "Tranzactie actualizata."                                | se confirma actualizarea                                     |
| 7           |                                                          | se listeaza toate tranzactiile                               |
|             | "01.12.2024 | 1200 | intrare"                            | afisare tranzactii                                           |
|             | "02.12.2024 | 500  | iesire"                             | afisare tranzactii                                           |
| 8           | "Sold curent: 700"                                       | se afiseaza soldul curent calculat                           |
| 9           | "Suma minima (int):"                                     | se cere o valoare minimă                                     |
| 800         |                                                           | utilizatorul introduce suma minimă                          |
|             | "Tranzactii cu sume > valoarea data:"                    | se afiseaza tranzactiile cu suma peste 800                   |
|             | "01.12.2024 | 1200 | intrare"                            | afisare rezultat                                             |
| 10          | "Zi limita (zz.ll.aaaa):"                                | se cere o data limita                                        |
| 03.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Suma minima (int):"                                     | se cere suma minimă                                          |
| 1000        |                                                           | utilizatorul introduce suma                                 |
|             | "Tranzactii inainte de zi si cu sume > valoarea data:"   | se afiseaza rezultatele corespunzatoare                      |
|             | "01.12.2024 | 1200 | intrare"                            | afisare rezultat                                             |
| 11          | "Tip tranzactie cautat (intrare/iesire):"                | se cere tipul tranzactiei                                    |
| iesire      |                                                           | utilizatorul introduce tipul                                |
|             | "Tranzactii de tipul cerut:"                             | se afiseaza tranzactiile corespunzatoare                     |
|             | "02.12.2024 | 500 | iesire"                              | afisare rezultat                                             |
| 12          | "Tip pentru raport (intrare/iesire):"                    | se cere tipul pentru raport                                  |
| intrare     |                                                           | utilizatorul introduce tipul                                |
|             | "Suma totala pentru tipul intrare: 1200"                 | se afiseaza suma totala pentru acel tip                      |
| 13          | "Data pentru calcul sold (zz.ll.aaaa):"                  | se cere data pentru care se calculeaza soldul                |
| 02.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Sold la data 02.12.2024: 700"                           | se afiseaza soldul calculat                                  |
| 14          | "Tip tranzactie (intrare/iesire):"                       | se cere tipul tranzactiilor pentru ordonare                  |
| intrare     |                                                           | utilizatorul introduce tipul                                |
|             | "Ordine (crescator/descrescator):"                       | se cere ordinea de afisare                                   |
| descrescator|                                                           | utilizatorul introduce ordinea                              |
|             | "Tranzactii ordonate dupa suma:"                         | se afiseaza lista ordonata dupa suma                         |
|             | "01.12.2024 | 1200 | intrare"                            | afisare rezultat                                             |
| 4           | "Data pentru stergere (zz.ll.aaaa):"                     | se cere data pentru stergere                                 |
| 02.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Stergere completa pentru data data."                    | se confirma stergerea tranzactiilor la acea data             |
| 5           | "Data inceput (zz.ll.aaaa):"                             | se cere data de inceput a intervalului                       |
| 01.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Data final (zz.ll.aaaa):"                               | se cere data de final a intervalului                         |
| 03.12.2024  |                                                           | utilizatorul introduce data                                 |
|             | "Stergere in interval efectuata."                        | se confirma stergerea in interval                            |
| 6           | "Tip tranzactie de sters (intrare/iesire):"              | se cere tipul tranzactiei pentru stergere                    |
| intrare     |                                                           | utilizatorul introduce tipul                                |
|             | "Stergere dupa tip efectuata."                           | se confirma stergerea dupa tip                               |


---

## Lista de activitati

- [x] Implementare functii de validare a datelor (`an_bisect`, `este_data`)
- [x] Functii pentru adaugare si actualizare tranzactii
- [x] Functii pentru stergere tranzactii
- [x] Functii de filtrare
- [x] Functii de cautare 
- [x] Functii de raportare 
- [x] Calcul sold curent in functie de tip (`intrare` / `iesire`)
- [x] Interfata de tip consola pentru interactiune
- [ ] Functie de undo
- [ ] Teste suplimentare
- [ ] Refactorizare modulara (UI / logica)
- [x] Documentatie finala cu scenarii si exemple de rulare
