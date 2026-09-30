#include <stdio.h>
#include <stdlib.h>

// cerinta 1 ----------------------------------------------

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
        matrix[b-1][a-1] = 1;
    }

    return matrix;
}

int nr_of_edges_from_text(FILE* f){
    int a = 0;

    char linie[100];
    while (fgets(linie, 100, f) != NULL) {
        a++;
    }

    a--;
    return a;
}

int nr_of_vertex_from_text(FILE* f){
    char linie[100];
    fgets(linie, 100, f);

    int n = atoi(linie);
    return n;
}



int** ad_matrix_to_list(int** matrix, int n){ // neighbours start from 1 in the txt file, array indexes start from 0
    int** list = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i<n; i++){
        int* vertex = (int*) malloc(n*sizeof(int));
        list[i] = vertex;
        for (int j = 0; j<n; j++){  
            list[i][j] = -1; // no negative vertices, so -1 will mean end of neighbours
        }
    }

    for (int i = 0; i<n; i++){
        int current_pos = 0;
        for (int j = 0; j<n; j++){
            if (matrix[i][j] == 1){
                list[i][current_pos] = j+1; 
                current_pos ++;
            }
        }
    }

    return list;
}


int** list_to_in_matrix(int** list, int nr_edges, int n){ // neighbours start from 1 in the txt file, array indexes start from 0

    int** matrix = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i<n; i++){
        int* vertex = (int*) malloc(nr_edges*sizeof(int));
        matrix[i] = vertex;
        for (int j = 0; j<nr_edges; j++){  
            matrix[i][j] = 0;
        }
    }
    
    int edge = 0;


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n && list[i][j] != -1; j++){
            int v = list[i][j]-1;
                if (i < v){
                    matrix[i][edge] = 1;
                    matrix[v][edge] = 1;
                    edge++;
                }
        }
    }

    return matrix;
}

// cerinta 2 ----------------------------------------------

// a ---
int* noduri_izolate_from_text(FILE* f){
    int** ad_matrix = text_to_ad_matrix(f);
    int n = nr_of_vertex_from_text(f);

    int* result = (int*) malloc(n*sizeof(int));
    for (int j = 0; j<n; j++){  
        result[j] = -1; 
    }

    int current_pos = 0;
    int** ad_list = ad_matrix_to_list(ad_matrix, n);
    for (int i = 0; i < n; i++){
        if (ad_list[i][0] == -11) {
            result[current_pos] = i+1;
            current_pos++;
        }
    }

    return result;

}

// b ---
int este_regular_from_text(FILE* f){
    int n = nr_of_vertex_from_text(f);
    rewind(f);

    int** ad_matrix = text_to_ad_matrix(f);

    int grad = 0;
    for (int j = 0; j < n; j++){
        grad += ad_matrix[0][j];
    }

    for (int i = 1; i < n; i++){
        int grad_curent = 0;
        for (int j = 0; j < n; j++){
            grad_curent += ad_matrix[i][j];
        }
        if (grad_curent != grad){
            free_matrix(n, ad_matrix);
            return 0;
        }
    }

    free_matrix(n, ad_matrix);
    return 1;
}

// c ---
int** matricea_distantelor_from_text(FILE* f){
    int n = nr_of_vertex_from_text(f);
    rewind(f);

    int** ad_matrix = text_to_ad_matrix(f);
    int INF = 1000000;

    int** distante = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++){
        distante[i] = (int*) malloc(n*sizeof(int));
        for (int j = 0; j < n; j++){
            if (i == j){
                distante[i][j] = 0;
            } else if (ad_matrix[i][j] == 1){
                distante[i][j] = 1;
            } else {
                distante[i][j] = INF;
            }
        }
    }

    // Roy-Floyd
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (distante[i][k] != INF && distante[k][j] != INF &&
                    distante[i][k] + distante[k][j] < distante[i][j]){
                    distante[i][j] = distante[i][k] + distante[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (distante[i][j] == INF){
                distante[i][j] = -1;
            }
        }
    }

    free_matrix(n, ad_matrix);
    return distante;
}

// d ---
int este_conex_from_text(FILE* f){ // DFS
    int n = nr_of_vertex_from_text(f);
    rewind(f);

    int** ad_matrix = text_to_ad_matrix(f);

    int* vizitat = (int*) calloc(n, sizeof(int));
    int* stiva = (int*) malloc(n*sizeof(int));
    int top = 0;

    stiva[top++] = 0;
    vizitat[0] = 1;

    while (top > 0){
        int nod = stiva[--top];
        for (int v = 0; v < n; v++){
            if (ad_matrix[nod][v] == 1 && vizitat[v] == 0){
                vizitat[v] = 1;
                stiva[top++] = v;
            }
        }
    }

    for (int i = 0; i < n; i++){
        if (vizitat[i] == 0){
            free(vizitat);
            free(stiva);
            free_matrix(n, ad_matrix);
            return 0;
        }
    }

    free(vizitat);
    free(stiva);
    free_matrix(n, ad_matrix);
    return 1;
}


// misc ----------------------------------------------

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

int main(){

    // cerinta 1 ----------------------------------------------

    FILE* f = fopen("in.txt", "r");

    int n = nr_of_vertex_from_text(f);
    fclose(f);
    f = fopen("in.txt", "r");
    
    int nr_edges = nr_of_edges_from_text(f);
    fclose(f);
    f = fopen("in.txt", "r");

    int** ad_matrix = text_to_ad_matrix(f);
    fclose(f);
    f = fopen("in.txt", "r");
    printf("Matrice adiacenta: \n");
    print_matrix(n, n, ad_matrix);
    fclose(f);

    int** lista_ad = ad_matrix_to_list(ad_matrix, n);
    printf("Lista adiacenta: \n");
    print_matrix(n, n, lista_ad);

    int** in_matrix = list_to_in_matrix(lista_ad, nr_edges, n);
    printf("Matrice incidenta: \n");
    print_matrix(n, nr_edges, in_matrix);

    free_matrix(n, ad_matrix);
    free_matrix(n, lista_ad);
    free_matrix(n, in_matrix);
    
    // cerinta 2 ----------------------------------------------

    f = fopen("in.txt", "r");
    int* noduri_izolate = noduri_izolate_from_text(f);
    fclose(f);
    printf("Noduri izolate: ");
    for (int i = 0; i < n && noduri_izolate[i] != -1; i++){
        printf("%d ", noduri_izolate[i]);
    }
    printf("\n\n");
    free(noduri_izolate);

    f = fopen("in.txt", "r");
    int regular = este_regular_from_text(f);
    fclose(f);
    printf("Este regular: %d\n\n", regular);

    f = fopen("in.txt", "r");
    int** distante = matricea_distantelor_from_text(f);
    fclose(f);
    printf("Matricea distantelor: \n");
    print_matrix(n, n, distante);
    free_matrix(n, distante);

    f = fopen("in.txt", "r");
    int conex = este_conex_from_text(f);
    fclose(f);
    printf("Este conex: %d\n", conex);

    return 0;
}
