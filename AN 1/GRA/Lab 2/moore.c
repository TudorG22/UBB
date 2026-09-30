#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------- cerinta 1 ----------------------------------------------

// ---------------- utils ----------------

int** text_to_ad_matrix(FILE* f){ // se presupune ca pentru n varfuri, in fisier sunt notate de la 1 la n, nu de la 0

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

void print_path_matrix(int n, int m, int** matrix) {
    for (int i = 0; i < n; i++) {
        printf("%d: ", i+1);
        if (matrix[i][0] == -1) {
            printf("Nu este drum\n");
            continue;
        }

        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == -1) {
                break;
            }
            if (j > 0) {
                printf("->");
            }
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// ---------------- Queue ----------------

typedef struct {
    int* data;
    int head;
    int tail;
    int capacity;
} Queue;

Queue* queue_create(int capacity) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->data = (int*) malloc(capacity * sizeof(int));
    q->head = 0;
    q->tail = 0;
    q->capacity = capacity;
    return q;
}

int queue_is_empty(Queue* q) {
    return q->head == q->tail;
}

void queue_push(Queue* q, int value) {
    q->data[q->tail++] = value;
}

int queue_pop(Queue* q) {
    return q->data[q->head++];
}

void queue_free(Queue* q) {
    free(q->data);
    free(q);
}

// ---------------- Moore ----------------

int** moore(int** ad_matrix, int n, int s){

    int** paths = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i<n; i++){
        int* line = (int*) malloc(n*sizeof(int));
        paths[i] = line;
        for (int j = 0; j<n; j++){
            paths[i][j] = -1;
        }
    }

    int dist[n];
    int parent[n];
    for (int i = 0; i<n; i++){
        dist[i] = -1;
        parent[i] = -1;
    }
    dist[s] = 0;

    Queue* q = queue_create(n);
    queue_push(q, s);

    int u;
    while (!queue_is_empty(q)){
        u = queue_pop(q);
        for (int v = 0; v<n; v++){
            if ((ad_matrix[u][v] == 1) && (dist[v] == -1)){
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue_push(q, v);
            }
        }
    }

    // paths
    for (int v = 0; v < n; v++) {
        if (dist[v] != -1) {
            int tmp[n];
            int len = 0;
            int current = v;
            while (current!= -1) {
                tmp[len++] = current + 1;
                current = parent[current];
            }
            for (int i = 0; i < len; i++) {
                paths[v][i] = tmp[len - 1 - i];
            }
        }
    }

    queue_free(q);
    return paths;
}



// ---------------- main ----------------

int main(){
    FILE* f = fopen("graf.txt", "r");

    int n = nr_of_vertex_from_text(f);
    fclose(f);
    f = fopen("graf.txt", "r");


    int** ad_matrix = text_to_ad_matrix(f);
    fclose(f);

    int s;
    printf("Sursa: ");
    scanf("%d", &s);
    s = s - 1;

    int** paths = moore(ad_matrix, n, s);
    print_path_matrix(n, n, paths);
    free_matrix(n, paths);
    free_matrix(n, ad_matrix);
    
    return 0;
}
