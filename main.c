#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Interfaces.h"
#include "Interval.h"
#include "Node.h"
#include "Utile.h"
//
// Created by ZHANG ANXIAN AND MIGUEU BRYAN on 12/5/2024.
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
    //showPeriod(tree, period);
    //free(tree);
    deleteAll(tree);
    tree = NULL;
    showTree(tree);
}

int main() {
    // time(); // essayer de récupérer l'année accutuele

    // test(); // fonction utilsier pour les testes en dure
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

    char choice = ' ';

    while (choice != '7') {
        printf("#################### MENU ####################\n");
        printf("| 1. Show all reservations\n");
        printf("| 2. Show all reservations of a company\n");
        printf("| 3. Show all reservations of within a period\n");
        printf("| 4. Add a reservation\n");
        printf("| 5. Update a reservation\n");
        printf("| 6. Delete a reservation\n");
        printf("| 7. Leave\n");
        printf("##############################################\n");

        choice = getUserNumber("Enter your choice:") + '0'; // convert to char

        switch (choice) {
            case '1':
                interfaceShowTree(tree);
                break;
            case '2':
                interfaceShowCompany(tree);
                break;
            case '3':
                interfaceShowPeriod(tree);
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                printf("\n======== PROGRAM FINISHED ========\n");
                break;
            default:
                printf("\n\nERROR : INVALID CHOICE ! ");
        }

        emptyBuffer();
        printf("\n\n\n");
    }

    deleteAll(tree);
    tree = NULL;

    return 0;
}
