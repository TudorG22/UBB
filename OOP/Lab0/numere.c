#include <stdio.h> 

int main(){
    int n;
    printf("n = ");
    scanf("%d", &n);

    int suma = 0;
    int temp;

    for (int i = 0; i < n; i++){
        printf("numar %d = ", i+1);
        scanf("%d", &temp);
        suma = suma + temp;
    }

    printf("Suma este %d\n", suma);
}
