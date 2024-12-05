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
    i->end = 214;

    Interval *i2 = malloc(sizeof(Interval));
    i2->start = 225;
    i2->end = 402;

    Interval *i3 = malloc(sizeof(Interval));
    i3->start = 613;
    i3->end = 1025;

    Interval *i4 = malloc(sizeof(Interval));
    i4->start = 101;
    i4->end = 107;

    Interval *i5 = malloc(sizeof(Interval));
    i5->start = 220;
    i5->end = 328;

    Tree tree = createNode(1, "J'aime les pommes au cafe", i);
    tree->right = createNode(2, "pomme ?", i2);
    tree->right->right = createNode(3, "cafe ?", i3);
    tree->right->left = createNode(3, "the ?", i5);

    tree->left = createNode(4, "1e fruit ?", i4);

    Interval *period = malloc(sizeof(Interval));
    period->start = 701;
    period->end = 1230;

    //showTree(tree);

    // ========== LE CAS OU LA PERIODE OU NUM ENREPISE INDIQUER EXISTE PAS N'EST PAS ENCORE TRAITE ==========
    //showCompany(tree, 1);
    showPeriod(tree, period);

}

int main() {
    test(); // fonction utilsier pour les testes en dure

    return 0;
}
