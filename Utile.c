//
// Created by gadan on 12/6/2024.
//

#include "Utile.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void emptyBuffer() {
    char c = ' ';
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int getUserNumber(const char *message) {
    unsigned int number = 0;

    printf("%s", message);
    scanf("%d", &number);
    emptyBuffer();

    return number;
}

char *getUserString(const char *message) {
    char *buffer = (char *) malloc(100 * sizeof(char));
    if (buffer == NULL) {
        printf("ERROR IN MALLOC.\n");
        exit(1); // exit the program
    }

    printf("%s", message);
    fgets(buffer, 100, stdin);

    unsigned int size = strlen(buffer);

    if (size > 0 && buffer[size - 1] == '\n') {
        buffer[size - 1] = '\0';
    }

    emptyBuffer();

    return buffer;
}
