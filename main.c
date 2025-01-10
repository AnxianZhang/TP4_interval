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

int main() {
    Tree tree = NULL;

    char choice = ' ';

    while (choice != 'Q') {
        printf("#################### MENU ####################\n");
        printf("| 1. Show all reservations\n");
        printf("| 2. Show all reservations of a company\n");
        printf("| 3. Show all reservations of within a period\n");
        printf("| 4. Add a reservation\n");
        printf("| 5. Update a reservation\n");
        printf("| 6. Delete a reservation\n");
        printf("| 7. Search a reservation\n");
        printf("| 8. Show the number of reservation of all companies\n");
        printf("| A. Export reservation(s) to CSV\n");
        printf("| B. Import reservation(s)\n");
        printf("| Q. Leave\n");
        printf("##############################################\n");

        choice = getUserString("Enter your choice:")[0]; // convert to char

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
                interfaceAddreservation(&tree);
                break;
            case '5':
                interfaceUpdateReservation(&tree);
                break;
            case '6':
                interfaceDeletereservaion(&tree);
                break;
            case '7':
                interfaceSearchReservation(tree);
                break;
            case '8':
                interfaceShowyCompaniesReservation(tree);
                break;
            case 'A':
                interfaceExportData(tree);
                break;
            case 'B':
                interfaceImportData(&tree);
                break;
            case 'Q':
                printf("\n========== PROGRAM FINISHED ==========\n");
                printf("\n======== PRESS ENTER TO FINISH ========\n");

                break;
            default:
                printf("\n\nERROR : INVALID CHOICE ! ");
        }

        emptyBuffer();
        printf("\n\n\n");
    }

    printf("\n");

    deleteAll(tree);
    tree = NULL;

    return 0;
}
