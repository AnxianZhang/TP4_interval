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


    char *chaine = (char *)malloc(100 * sizeof(char));
    if (chaine == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);  // exit the program
    }

    printf("%s", message);
    fgets(chaine, 1000, stdin);

    emptyBuffer();

    return chaine;
}

