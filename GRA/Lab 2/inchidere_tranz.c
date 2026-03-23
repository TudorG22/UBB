#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------- cerinta 2 ----------------------------------------------

// ---------------- utils ----------------

int** text_to_ad_matrix(FILE* f){

    char linie[100];

    fgets(linie, 100, f);

    int n = atoi(linie);

    int** matrix = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i<n; i++){
        int* vertex = (int*) malloc(n*sizeof(int));
        matrix[i] = vertex;
        for (int j = 0; j<n; j++){  
            matrix[i][j] = 0;
        }
    }

    int a, b;

    while (fgets(linie, 100, f) != NULL) {
        sscanf(linie, "%d %d", &a, &b);
        matrix[a-1][b-1] = 1;
    }

    return matrix;
}

int nr_of_vertex_from_text(FILE* f){
    char linie[100];
    fgets(linie, 100, f);

    int n = atoi(linie);
    return n;
}

void print_matrix(int n, int m, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != -1) {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n\n");
    }
}

void free_matrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// ---------------- Inchidere ----------------

void inchidere_tranzitiva(int n, int** T) {
    for (int i = 0; i < n; i++) {
        T[i][i] = 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
            }
        }
    }
}


// ---------------- main ----------------

int main(){
    FILE* f = fopen("graf.txt", "r");

    int n = nr_of_vertex_from_text(f);
    fclose(f);
    f = fopen("graf.txt", "r");
    

    int** ad_matrix = text_to_ad_matrix(f);
    fclose(f);


    printf("Matricea inchederii tranzitive: \n");
    inchidere_tranzitiva(n, ad_matrix);
    print_matrix(n, n, ad_matrix);
    free_matrix(n, ad_matrix);
    
    return 0;
}
