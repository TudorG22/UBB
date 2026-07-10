#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int rows[10000][100];
int sizes[10000];
int results[10000];
int idx[10000];

void* add_row(void* arg) {
    int k = *(int*)arg;
    int sum = 0;

    for (int i = 0; i < sizes[k]; i++) {
        sum += rows[k][i];
    }

    results[k] = sum;
    return NULL;
}

int main() {
    FILE *f = fopen("fisier.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 1;
    }

    pthread_t threads[10000];

    int r = 0;
    char s[100];
    while (fgets(s, sizeof(s), f) != NULL) {
        int n = 0;
        char *p = strtok(s, " \n");

        while (p != NULL) {
            rows[r][n++] = atoi(p);
            p = strtok(NULL, " \n");
        }

        sizes[r] = n;
        idx[r] = r;
        pthread_create(&threads[r], NULL, add_row, &idx[r]);
        r += 1;
    }

    for (int i = 0; i < r; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d finished. \n", i);
    }

    for (int i = 0; i < r; i++) {
        printf("%d\n", results[i]);
    }

    fclose(f);
    return 0;
}
