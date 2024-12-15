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

int getIdUnique(const Tree tree) {
    if (tree) {
        int id = getUserNumber("Which id reservation you want to add ?: ");
        while (searchId(tree, id) == 1) {
            printErrorTreeMessages("\nthis Id already exist\n");
            id = getUserNumber("Which id reservation you want to add ?: ");
        }
        return id;
    }
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

int hasTreeAndLeftRight(const Tree tree) {
    return tree != NULL && tree->left != NULL && tree->right != NULL;
}

void printErrorTreeMessages(const char *specificMessage) {
    printf("%s\n", specificMessage);
    printf("Please try again\n\n");
}

void printErrorMessages(const char *specificMessage) {
    // it's for bryan
    printf("%s\n", specificMessage);
    printf("Please try again later: ");
}

void printEmptyTreeMessages() {
    printErrorTreeMessages("There are no reservations for the moment");
}

void interfaceShowTree(const Tree tree) {
    if (!hasTreeAndLeftRight(tree)) {
        printEmptyTreeMessages();
        return;
    }
    printf("The reservations are:\n");
    showTree(tree);
}

void interfaceShowCompany(const Tree tree) {
    unsigned int id = getUserNumber("Which company reservation you want to show ?");

    if (!hasTreeAndLeftRight(tree)) {
        printEmptyTreeMessages();
        return;
    }

    if (!showCompany(tree, id)) {
        char messageBuffer[MAX_BUFFER_SIZE + 1] = {""};

        snprintf(messageBuffer, MAX_BUFFER_SIZE + 1, "The company number %d haven't make reservation !", id);
        printErrorTreeMessages(messageBuffer);
    }
}

void interfaceShowPeriod(const Tree tree) {
    Interval i;

    askForInterval(&i);

    if (!hasTreeAndLeftRight(tree)) {
        printEmptyTreeMessages();
        return;
    }

    if (!showPeriod(tree, &i)) {
        char *startDateBuffer = getParsedDate(i.start);
        char *endDateBuffer = getParsedDate(i.end);
        char messageBuffer[MAX_BUFFER_SIZE + 1] = {""};

        snprintf(
            messageBuffer,MAX_BUFFER_SIZE + 1,
            "There are no reservation in the period of %s to %s !",
            startDateBuffer, endDateBuffer
        );
        printErrorTreeMessages(messageBuffer);
    }
}

void interfaceAddreservation(const Tree tree) {
    int id = getIdUnique(tree);
    Interval *interval = malloc(sizeof(Interval));

    askForInterval(interval);

    char *description = getUserString("\nDescription reservation you want to add:");
    addReservation(tree, id, interval, description);
}

void interfaceUpdateReservation(const Tree tree) {
    int id = getUserNumber("Which id reservation you want to update ?:");
    Interval *current = malloc(sizeof(Interval));
    Interval *newInterval = malloc(sizeof(Interval));

    printf("\n*******> current interval");
    askForInterval(current);

    printf("\n*******> new interval");
    askForInterval(newInterval);

    updateReservation(tree, current, newInterval, id);
}

// void interfaceDeletereservaion(const Tree tree) {
//     int id=1;
//     Interval *i = malloc(sizeof(Interval));
//     i->start =110;
//     i->end =214;
//     deleteReservation(tree, i, id);
// }

void interfaceDeletereservaion(const Tree tree) {
    int id = getUserNumber("Which id reservation you want to delete ?: ");
    Interval *current = malloc(sizeof(Interval));

    askForInterval(current);

    deleteReservation(tree, current, id);
}

void interfaceSearchReservation(const Tree tree) {
    int id=1;
    Interval *i = malloc(sizeof(Interval));
    i->start =110;
    i->end =214;
    Node *node = searchReservation(tree, i, id);

    if (node) {
        char *startDate = getParsedDate(node->interval->start);
        char *endDate = getParsedDate(node->interval->end);

        printf("\n--------> votre reservation <-----------");
        printf("\n id: %d", node->id);
        printf("\nstart date :%s", startDate);
        printf("\nend date :%s", endDate);
        printf("\ndescription: %s", node->description);
        printf("\n----------------------------------------\n");
    } else {
        printErrorTreeMessages("\n votre reservation not found");
    }
}

// void interfaceSearchReservation(const Tree tree) {
//     int id = getUserNumber("\nWhich id reservation you want to search?: ");
//     Interval current;
//
//     askForInterval(&current);
//
//     Node *node = searchReservation(tree, &current, id);
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
