#include <stdio.h>
#include <string.h>

int main(void) {
    char text[256];

    printf("Enter text: ");
    if (!fgets(text, sizeof(text), stdin)) {
        return 1;
    }

    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    printf("Program three: reversed = ");
    for (size_t i = 0; i < len; i++) {
        putchar(text[len - 1 - i]);
    }
    putchar('\n');

    return 0;
}
