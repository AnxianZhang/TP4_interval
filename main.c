#include <stdio.h>
#include <stdlib.h>

#include "Interval.h"
#include "Node.h"
//
// Created by gadan on 12/5/2024.
//

void test() {
    Interval *i = malloc(sizeof(Interval));
    i->start = 110;
    i->end = 225;

    Interval *i2 = malloc(sizeof(Interval));
    i2->start = 225;
    i2->end = 402;

    Interval *i3 = malloc(sizeof(Interval));
    i3->start = 613;
    i3->end = 1025;

    Interval *i4 = malloc(sizeof(Interval));
    i4->start = 101;
    i4->end = 107;

    Tree tree = createNode(1, "J'aime les pommes au cafe", i);
    tree->right = createNode(2, "pomme ?", i2);
    tree->right->right = createNode(3, "cafe ?", i3);
    tree->left = createNode(4, "1e fruit ?", i4);

    showTree(tree);
}

int main() {
    test(); // fonction utilsier pour les testes en dure

    return 0;
}
