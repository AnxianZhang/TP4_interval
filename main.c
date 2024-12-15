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

    // Interval *i2 = malloc(sizeof(Interval));
    // i2->start = 225;
    // i2->end = 402;
    //
    // Interval *i3 = malloc(sizeof(Interval));
    // i3->start = 1013;
    // i3->end = 1025;
    //
    // Interval *i4 = malloc(sizeof(Interval));
    // i4->start = 101;
    // i4->end = 107;
    //
    // Interval *i5 = malloc(sizeof(Interval));
    // i5->start = 220;
    // i5->end = 224;

    // =================== TEST MANUELLE ===========
    // Tree tree = createNode(1, "J'aime les pommes au cafe", i);
    // tree->right = createNode(2, "pomme ?", i2);
    // tree->right->right = createNode(3, "cafe ?", i3);
    // tree->right->left = createNode(3, "the ?", i5);
    //
    // tree->left = createNode(4, "1e fruit ?", i4);
    //
    // Interval *period = malloc(sizeof(Interval));
    // period->start = 701;
    // period->end = 1230;

    // =================== TEST AVEC UNIQUEMENT AVEC LA FONCTION AJOUTE ===========
    Tree tree = malloc(sizeof(Tree));
    tree->left=NULL;
    tree->right=NULL;
    tree->interval=NULL;
    addReservation(tree, 1, i, "J'aime les pommes au cafe");
    interfaceSearchReservation(tree);
   // interfaceShowTree(tree);
    //
    //addReservation(tree, 11, i2, "pomme ?");
    // //tree->right = createNode(11, "pomme ?", i2);
    // addReservation(tree, 111, i3, "cafe ?");
    //
    // //tree->right->right = createNode(111, "cafe ?", i3);
    // addReservation(tree, 110, i5, "the ?");
    //
    // //tree->right->left = createNode(110, "the ?", i5);
    // addReservation(tree, 10, i4, "1e frui t ?");
    //
    // //tree->left = createNode(10, "1e fruit ?", i4);
    //


    // Interval *i6 = malloc(sizeof(Interval));
    // i6->start = 108;
    // i6->end = 109;
    //
    // addReservation(tree, 13, i6, "crash test");


    // Interval *i7 = malloc(sizeof(Interval));
    // i7->start = 101;
    // i7->end = 102;
    //
    // addReservation(tree, 14, i4, "crash");

    // Interval *periodeToShow = malloc(sizeof(Interval));
    // periodeToShow->start = 108;
    // periodeToShow->end = 1209;
    //showTree(tree);
    //printf("\n");
    //interfaceShowPeriod(tree);

    char choice = ' ';

    // while (choice != '8') {
    //     printf("#################### MENU ####################\n");
    //     printf("| 1. Show all reservations\n");
    //     printf("| 2. Show all reservations of a company\n");
    //     printf("| 3. Show all reservations of within a period\n");
    //     printf("| 4. Add a reservation\n");
    //     printf("| 5. Update a reservation\n");
    //     printf("| 6. Delete a reservation\n");
    //     printf("| 7. Search a reservation\n");
    //     printf("| 8. Leave\n");
    //     printf("##############################################\n");
    //
    //     choice = getUserNumber("Enter your choice:") + '0'; // convert to char
    //
    //     switch (choice) {
    //         case '1':
    //             interfaceShowTree(tree);
    //             break;
    //         case '2':
    //             interfaceShowCompany(tree);
    //             break;
    //         case '3':
    //             interfaceShowPeriod(tree);
    //             break;
    //         case '4':
    //             interfaceAddreservation(tree);
    //             break;
    //         case '5':
    //             interfaceUpdateReservation(tree);
    //             break;
    //         case '6':
    //             interfaceDeletereservaion(tree);
    //             break;
    //         case '7':
    //             interfaceSearchReservation(tree);
    //             break;
    //         case '8':
    //             printf("\n======== PROGRAM FINISHED ========\n");
    //             break;
    //         default:
    //             printf("\n\nERROR : INVALID CHOICE ! ");
    //     }
    //
    //     emptyBuffer();
    //     printf("\n\n\n");
    // }

    printf("\n");

    deleteAll(tree);
    tree = NULL;

    return 0;
}
