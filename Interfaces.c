//
// Created by Bryan on 15/12/2024.
//

#include "Interfaces.h"

#include <stdio.h>

#include <stdlib.h>

#include "Utile.h"

#include "Node.h"

#include "interval.h"

// void interfaceAddreservation(const Tree tree) {
//     int id=20;
//     Interval *i = malloc(sizeof(Interval));
//     i->start =705;
//     i->end =707;
//     char description[50]="pppppppppppppppp";
//     addReservation(tree, id, i, &description);
// }
int searchId(Tree tree, int id) {
    if (tree == NULL)
        return 0;
    if (tree->id == id)
        return 1;
    return searchId(tree->left, id) || searchId(tree->right, id);
}

int numberOfDaysInMonth(int month) {
    if (month == 2)
        return 29;
    if (month <= 7)
        return 30 + month % 2;
    return 31 - month % 2;
}

int getUserValideDate() {
    int month, day;

    do {
        month = getUserNumber("enter the number of your month:");
        if (month >= 1 && month <= 12) break;
        printErrorTreeMessages("Incorrect month number entered");
    } while (1);

    do {
        day = getUserNumber("enter the number of your day:");
        if (day >= 1 && day <= numberOfDaysInMonth(month)) break;
        printErrorTreeMessages("Incorrect day number entered");
    } while (1);

    return month * 100 + day;
}

void askForInterval(Interval *i) {
    printf("\n*******> start date\n");
    i->start = getUserValideDate();

    printf("\n*******> end date\n");
    i->end = getUserValideDate();

    while (comparatorDate(i->end, i->start) != 1) {
        printErrorTreeMessages("Start date must begin before end date !");
        i->end = getUserValideDate();
    }
}

void printErrorTreeMessages(const char *specificMessage) {
    printf("%s\n", specificMessage);
    printf("Please try again\n\n");
}

void printEmptyTreeMessages() {
    printErrorTreeMessages("There are no reservations for the moment");
}

void interfaceShowTree(const Tree tree) {
    if (!tree) {
        printEmptyTreeMessages();
        return;
    }
    printf("---------------------> ALL RESERVATIONS <---------------------\n");
    showTree(tree);
    printf("--------------------------------------------------------------\n");
}

void interfaceShowCompany(const Tree tree) {
    unsigned int id = getUserNumber("Which company reservation you want to show ?");

    if (!tree) {
        printEmptyTreeMessages();
        return;
    }

    printf("---------------------> ALL RESERVATIONS FOR THE %d COMPANY<---------------------\n", id);

    if (!showCompany(tree, id))
        printErrorTreeMessages("This company haven't make a reservation yet !");

    printf("------------------------------------------------------------------------------\n");
}

void interfaceShowPeriod(const Tree tree) {
    Interval i;
    askForInterval(&i);

    if (!tree) {
        printEmptyTreeMessages();
        return;
    }

    char *startDateBuffer = getParsedDate(i.start);
    char *endDateBuffer = getParsedDate(i.end);

    printf(
        "---------------------> ALL RESERVATIONS WITHIN %s AND %s <---------------------\n",
        startDateBuffer,
        endDateBuffer
    );

    if (!showPeriod(tree, &i))
        printErrorTreeMessages("There are no reservation in this period !");

    printf("------------------------------------------------------------------------\n");
}

void interfaceAddreservation(Tree *tree) {
    int id = getUserNumber("enter your  id:  ");;
    Interval *interval = malloc(sizeof(Interval));

    askForInterval(interval);

    char *description = getUserString("\nDescription reservation you want to add:");
    addReservation(tree, id, interval, description);
}

void interfaceUpdateReservation(Tree *tree) {
    Interval *current = malloc(sizeof(Interval));
    Interval *newInterval = malloc(sizeof(Interval));

    printf("\n*******> current interval");
    askForInterval(current);

    printf("\n***************><***************");
    int id = getUserNumber("\n enter your new id: ");
    char *description = getUserString("\n enter your new description: ");

    printf("\n*******> new interval");
    askForInterval(newInterval);

    updateReservation(tree, current, newInterval, id, description);
}

// void interfaceDeletereservaion(Tree *tree) {
//     int id=1;
//     Interval *i = malloc(sizeof(Interval));
//     i->start =110;
//     i->end =214;
//     deleteReservation(tree, i);
// }

void interfaceDeletereservaion(Tree *tree) {
    Interval *current = malloc(sizeof(Interval));

    askForInterval(current);

    deleteReservation(tree, current);
}

// void interfaceSearchReservation(const Tree tree) {
//     int id=1;
//     Interval *i = malloc(sizeof(Interval));
//     i->start =110;
//     i->end =214;
//     Node *node = searchReservation(tree, i, id);
//
//     if (node) {
//         char *startDate = getParsedDate(node->interval->start);
//         char *endDate = getParsedDate(node->interval->end);
//
//         printf("\n--------> votre reservation <-----------");
//         printf("\n id: %d", node->id);
//         printf("\nstart date :%s", startDate);
//         printf("\nend date :%s", endDate);
//         printf("\ndescription: %s", node->description);
//         printf("\n----------------------------------------\n");
//     } else {
//         printErrorTreeMessages("\n votre reservation not found");
//     }
// }

void interfaceSearchReservation(const Tree tree) {
    Interval current;

    askForInterval(&current);

    Node *node = searchReservation(tree, &current);

    if (node) {
        char *startDate = getParsedDate(node->interval->start);
        char *endDate = getParsedDate(node->interval->end);

        printf("\n-----------> THE RESERVATION <-----------");
        printf("\nid: %d", node->id);
        printf("\nstart date: %s", startDate);
        printf("\nend date: %s", endDate);
        printf("\ndescription: %s", node->description);
        printf("\n-----------------------------------------\n");

        free(startDate);
        free(endDate);
    } else {
        printErrorTreeMessages("\n THE RESERVATION DOESN'T EXIST !");
    }
}
