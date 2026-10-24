#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int readInt(const char *prompt, int *value) {
    char line[100];
    char extra;
    long number;

    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;

    if (sscanf(line, " %ld %c", &number, &extra) != 1 ||
        number < -2147483647L - 1 || number > 2147483647L) {
        printf("Invalid input. Please enter a whole number.\n");
        return 0;
    }
    *value = (int)number;
    return 1;
}

void readLine(const char *prompt, char *destination, unsigned long size) {
    size_t length;
    printf("%s", prompt);
    if (fgets(destination, (int)size, stdin) == NULL) {
        destination[0] = '\0';
        return;
    }
    length = strlen(destination);
    if (length > 0 && destination[length - 1] == '\n') {
        destination[length - 1] = '\0';
    } else {
        clearInputBuffer();
    }
}
