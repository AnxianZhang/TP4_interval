#include <stdio.h>
#include <stdlib.h>

#include "Interval.h"
#include "Node.h"
//
// Created by Bryan on 12/5/2024.
//

void test() {
    Interval *i = malloc(sizeof(Interval));
    i->start = 0110;
    i->end = 1025;
    Node *n = createNode(1, "J'aime les pommes au cafe", i);
}

int main() {
    test(); // fonction utilsier pour les testes en dure

    return 0;
}
