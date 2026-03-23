#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr;

    fptr = fopen("matrix.txt", "r");

    char linie[100];

    fgets(linie, 100, fptr);

    int n = linie[0] - '0';
    int m = linie[2] - '0';

    int** matrice = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i<n; i++){
        int* line_m = (int*) malloc(m*sizeof(int));
        matrice[i] = line_m;
        fgets(linie, 100, fptr);
        for (int j = 0; j<m; j++){
            matrice[i][j] = linie[j*2] - '0';
        }
    }

    // fisier binar

    FILE *fptrtwo;
    fptrtwo = fopen("result.bin", "wb");

    fwrite(&n, sizeof(int), 1, fptrtwo);
    fwrite(&m, sizeof(int), 1, fptrtwo);

    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            int num = matrice[i][j];
            fwrite(&num, sizeof(int), 1, fptrtwo);
        }
    }

    for (int i = 0; i<n; i++){
        free(matrice[i]);
    }

    free(matrice);
    fclose(fptr);
    fclose(fptrtwo);

    return 0;
}