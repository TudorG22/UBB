#include <stdio.h> 

/*
Descriere:
    Determina numarul de zerouri de la sfarsitul unui numar n.

Parametri:
    n - numar intreg

Preconditii:
    n este numar intreg

Postconditii:
    returneaza numarul de zerouri de la sfarsitul lui n
*/

int numar_zero(int n){
    int k = 0;

    while (n != 0 && n % 10 == 0) {
        n = n / 10;
        k++;
    }

    return k;
}


/*
Descriere:
    Afiseaza un meniu si permite citirea unor numere pana la 0.
    Calculeaza produsul lor si afiseaza numarul de zerouri de la
    sfarsitul produsului.

Parametri:
    nu are parametri

Preconditii:
    utilizatorul introduce numere intregi nenule

Postconditii:
    se afiseaza numarul de zerouri ale produsului sau programul se opreste
*/

int main(){
    while (1){
        int comanda;
        printf("1) Ruleaza\n2) Exit\n");
        scanf("%d", &comanda);
        if (comanda == 2){
            return 0;
        }

        else {
            int produs = 1;
            int nr_citit = 1;
            while (nr_citit){
                scanf("%d", &nr_citit);
                if (nr_citit != 0){
                    produs = produs*nr_citit;
                }
            }     
            int nr = numar_zero(produs);
            printf("Numarul de zerouri e %d.\n", nr);
        }
    } 
}
