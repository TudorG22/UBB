#include <stdio.h> 

/*
Descriere:
    Determina exponentul primei p in descompunerea in factori primi a numarului n.
    Adica numarul maxim k pentru care p^k divide n.

Parametri:
    n - numarul in care cautam exponentul
    p - numar prim

Preconditii:
    n > 0
    p > 1
    p este numar prim

Postconditii:
    Functia returneaza k astfel incat p^k divide n
    si p^(k+1) nu divide n.
*/
int exponent_p(int n, int p) {
    int k = 0;

    while (n % p == 0) {
        n = n / p;
        k++;
    }

    return k;
}


/*
Descriere:
    Afiseaza un meniu si permite utilizatorului sa calculeze exponentul
    unui numar prim p in descompunerea numarului n.

Parametri:
    nu are parametri

Preconditii:
    utilizatorul introduce numere intregi pentru comenzi, n si p

Postconditii:
    daca se alege rularea, se afiseaza exponentul lui p in n;
    programul se opreste daca utilizatorul introduce comanda de iesire.
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
            int n; int p;
            printf("n: ");
            scanf("%d", &n);
            printf("p: ");
            scanf("%d", &p);
            
            int expo = exponent_p(n,p);
            printf("Exponentul lui %d in descompunerea lui %d e %d.\n", p, n, expo);
        }
    } 
}
