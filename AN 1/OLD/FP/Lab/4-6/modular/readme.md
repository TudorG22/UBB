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

### 1. Adaugare tranzactii
- Adauga o tranzactie cu data, suma si tip (`intrare` sau `iesire`).


### 2. Stergere tranzactii

- Sterge toate tranzactiile dintr-o perioada [data_inceput, data_final].

### 3. Filtrare
- `tranzactii_de_tip(tip)` → toate tranzactiile de un anumit tip (`intrare` sau `iesire`).


### 5. Afisari 
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
- Functii test

---

## Scenarii de rulare

## Scenarii de rulare

| utilizator                           | program                                           | descriere                                                |
|--------------------------------------|---------------------------------------------------|----------------------------------------------------------|
| add 01.12.2024 1000 intrare          |                                                   | utilizatorul adauga o tranzactie                        |
|                                      | "Tranzactie adaugata."                            | se confirma adaugarea                                   |
| add 02.12.2024 500 iesire            |                                                   | utilizatorul adauga o tranzactie                        |
|                                      | "Tranzactie adaugata."                            | se confirma adaugarea                                   |
| print                                |                                                   | se listeaza si se afiseaza soldul curent                |
|                                      | "Tranzactii:"                                     | afisare antet lista                                      |
|                                      | "  1. 01.12.2024 | 1000 | intrare"               | afisare tranzactie                                       |
|                                      | "  2. 02.12.2024 | 500  | iesire"                | afisare tranzactie                                       |
|                                      | "Sold curent: 500"                                | afisare sold curent                                      |
| undo                                 |                                                   | anuleaza ultima operatie                                 |
| print                                |                                                   | se listeaza si se afiseaza soldul curent                |
|                                      | "Tranzactii:"                                     | afisare antet lista                                      |
|                                      | "  1. 01.12.2024 | 1000 | intrare"               | afisare tranzactie                                       |
|                                      | "Sold curent: 1000"                               | afisare sold curent                                      |
| filter intrare                       |                                                   | elimina toate tranzactiile de tip intrare               |
|                                      | "Tranzactii de tipul cerut eliminate."            | confirmare filtrare                                      |
| print                                |                                                   | se listeaza si se afiseaza soldul curent                |
|                                      | "(fara tranzactii)"                               | nu exista tranzactii                                     |
|                                      | "Sold curent: 0"                                  | afisare sold curent                                      |
| add 03.12.2024 200 intrare           |                                                   | utilizatorul adauga o tranzactie                        |
|                                      | "Tranzactie adaugata."                            | confirmare                                               |
| add 04.12.2024 300 intrare           |                                                   | utilizatorul adauga o tranzactie                        |
|                                      | "Tranzactie adaugata."                            | confirmare                                               |
| add 05.12.2024 150 iesire            |                                                   | utilizatorul adauga o tranzactie                        |
|                                      | "Tranzactie adaugata."                            | confirmare                                               |
| delete 02.12.2024 04.12.2024         |                                                   | sterge tranzactiile in intervalul [02.12.2024, 04.12.2024] |
|                                      | "Stergere in interval efectuata."                 | confirmare stergere                                      |
| print                                |                                                   | se listeaza si se afiseaza soldul curent                |
|                                      | "Tranzactii:"                                     | afisare antet lista                                      |
|                                      | "  1. 05.12.2024 | 150  | iesire"                | afisare tranzactie                                       |
|                                      | "Sold curent: -150"                               | afisare sold curent                                      |
| undo                                 |                                                   | anuleaza ultima operatie                                 |
| print                                |                                                   | se listeaza si se afiseaza soldul curent                |
|                                      | "Tranzactii:"                                     | afisare antet lista                                      |
|                                      | "  1. 03.12.2024 | 200  | intrare"               | afisare tranzactie                                       |
|                                      | "  2. 04.12.2024 | 300  | intrare"               | afisare tranzactie                                       |
|                                      | "  3. 05.12.2024 | 150  | iesire"                | afisare tranzactie                                       |
|                                      | "Sold curent: 350"                                | afisare sold curent                                      |
| exit                                 |                                                   | inchidere program                                        |



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
- [x] Functie de undo
- [x] Teste 
- [x] Refactorizare modulara
- [x] Documentatie finala cu scenarii si exemple de rulare
