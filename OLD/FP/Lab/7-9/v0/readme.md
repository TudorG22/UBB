# 4 - Biblioteca

## Enunt
Scrieți o aplicație pentru o bibliotecă.
Aplicația stochează:
- cărți: <id>,<titlu>,<descriere>,<autor>,etc
- clienți: <id>, <nume>, <CNP>,etc
Creați o aplicație care permite:
- gestiunea listei de cărți și clienți.
- adaugă, șterge, modifică, lista de cărți, lista de clienți
- căutare carte, căutare clienți.
- Închiriere/returnare carte
- Rapoarte:
  - Cele mai inchiriate cărți.
  - Clienți cu cărți închiriate ordonat dupa: nume, după numărul de cărți închiriate
  - Primi 20% dintre cei mai activi clienți (nume client si numărul de cărți închiriate)

---

## Lista de functionalitati (implementate)

- Creare obiect carte
- Creare obiect client
- Creare lista de carti
- Creare lista de clienti
- Adaugare carte in lista de carti
- Stergere carte din lista de carti
- Inlocuire carte in lista de carti
- Golire lista de carti
- Afisarea listei de carti

- Adaugare client in lista de clienti
- Stergere client din lista de clienti
- Modificare client din lista de clienti
- Golire lista de clienti

- Adaugare carte imprumutata unui client
- Stergere carte imprumutata de la un client




## Plan de iteratii

### Iteratia 1
- realizat structura 
- implementat functiile de adaugare, stergere, si modificare a listelor de carti si de clienti

### Iteratia 2


### Iteratia 3 

---


## Scenarii de rulare

|     utilizator | program                                   | descriere                                    |                         
| -------------: | :---------------------------------------- | :------------------------------------------- | 
|              1 | `ID carte:`                               | se cere identificatorul cărții               |                         
|            101 |                                           | utilizatorul introduce ID-ul                 |                         
|                | `Titlu:`                                  | se cere titlul cărții                        |                         
|            Ion |                                           | utilizatorul introduce titlul                |                         
|                | `Autor:`                                  | se cere autorul cărții                       |                         
|       Rebreanu |                                           | utilizatorul introduce autorul               |                         
|                | `Descriere:`                              | se cere descrierea cărții                    |                         
|          roman |                                           | utilizatorul introduce descrierea            |                         
|                | `Cartea a fost adaugata.`                 | confirmare adăugare carte                    |                         
|              4 |                                           | utilizatorul selectează listarea cărților    |                        
|                | `[101. 'Ion' scrisa de Rebreanu]`         | se afișează lista curentă de cărți           |                        
|              6 | `ID client:`                              | se cere ID-ul clientului                     |                         
|             10 |                                           | utilizatorul introduce ID-ul                 |                         
|                | `Nume:`                                   | se cere numele clientului                    |                         
| Popescu Mircea |                                           | utilizatorul introduce numele                |                         
|                | `CNP:`                                    | se cere CNP-ul                               |                         
|  1920203123456 |                                           | utilizator introduce CNP                     |                         
|                | `Client adaugat.`                         | confirmare adăugare client                   |                         
|             10 | `ID client:`                              | se cere ID-ul clientului pentru împrumut     |                         
|             10 |                                           | utilizator introduce ID existent             |                         
|                | `ID carte de imprumutat:`                 | se cere ID carte                             |                         
|            101 |                                           | utilizator introduce ID carte                |                         
|                | `Cartea a fost adaugata la imprumuturi.`  | se confirmă împrumutul                       |                         
|             12 | `ID client:`                              | se cere ID-ul pentru afișarea împrumuturilor |                         
|             10 |                                           | utilizator introduce                         |                         
|                | `Client: 10 Popescu Mircea 1920203123456` | se afișează date client                      |                         
|                | `101. 'Ion' scrisa de Rebreanu`           | listă cărți împrumutate                      |                         
|             11 | `ID client:`                              | se cere ID-ul pentru returnare               |                         
|             10 |                                           | utilizator introduce                         |                         
|                | `ID carte de returnat:`                   | se cere cartea împrumutată                   |                         
|            101 |                                           | utilizator introduce                         |                         
|                | `Cartea a fost stearsa din imprumuturi.`  | confirmare returnare                         |                         
|              9 |                                           | utilizatorul selectează listarea clienților  |                         
|                | `10 Popescu Mircea 1920203123456   | imprumutate: 0`                                     |
|              7 | `ID client de sters:`                     | se cere ID-ul clientului de șters            |                         
|             10 |                                           | utilizator introduce                         |                         
|                | `Client sters.`                           | confirmare ștergere                          |                         
|              2 | `ID carte de sters:`                      | se cere ID carte de șters                    |                        
|            101 |                                           | utilizator introduce                         |                        
|                | `Cartea a fost stearsa.`                  | confirmare ștergere carte                    |                         
|             13 |                                           | utilizatorul selectează golire listă clienți |                         
|                | `Lista de clienti a fost golita.`         | confirmare                                   |                         
|              5 |                                           | utilizator selectează golire listă cărți     |                         
|                | `Lista de carti a fost golita.`           | confirmare                                   |                         
|              0 | `Iesire.`                                 | programul se închide                         |                         



