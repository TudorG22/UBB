#include <stdio.h>

int main(void) {
    int n;
    printf("How many numbers? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid count.\n");
        return 1;
    }

    double value;
    double total = 0.0;

    for (int i = 0; i < n; i++) {
        printf("number %d = ", i + 1);
        if (scanf("%lf", &value) != 1) {
            printf("Invalid number.\n");
            return 1;
        }
        total += value;
    }

    printf("Program four: average = %.2f\n", total / n);
    return 0;
}
