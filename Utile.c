//
// Created by gadan on 12/6/2024.
//

#include "Utile.h"

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
