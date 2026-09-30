#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <int1> <int2> ...\n", argv[0]);
        return 1;
    }

    long long sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += atoll(argv[i]);
    }

    printf("Program two: sum = %lld\n", sum);
    return 0;
}
