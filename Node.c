//
// Created by gadan on 12/5/2024.
//

#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(unsigned int id, char *description, Interval *interval) {
    if (!interval) return NULL;

    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;

    n->id = id;
    n->description = malloc(sizeof(char) * strlen(description));
    strcpy(n->description, description);
    n->interval = interval;
    n->left = NULL;
    n->right = NULL;

    return n;
}
