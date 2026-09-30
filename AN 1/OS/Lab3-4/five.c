#include <stdio.h>

int main(void) {
    int n;
    printf("Enter n (0..20): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 20) {
        printf("Invalid n.\n");
        return 1;
    }

    unsigned long long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= (unsigned long long)i;
    }

    printf("Program five: %d! = %llu\n", n, fact);
    return 0;
}
