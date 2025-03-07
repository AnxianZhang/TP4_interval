//
// Created by Bryan on 15/12/2024.
//

#include "Interfaces.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "Utile.h"

#include "Node.h"

#include "interval.h"

int searchId(const Tree tree, int id) {
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
    int id = getUserNumber("enter your  id:  ");
    Interval *interval = malloc(sizeof(Interval));
    if (!interval) {
        printf("MALLOC FAILED IN interfaceAddreservation");
        return;
    }

    askForInterval(interval);

    char *description = getUserString("\nDescription reservation you want to add:");
    addReservation(tree, id, interval, description);
}

void interfaceUpdateReservation(Tree *tree) {
    Interval *current = malloc(sizeof(Interval));
    if (!current) {
        printf("MALLOC FAILED IN interfaceUpdateReservation");
        return;
    }

    Interval *newInterval = malloc(sizeof(Interval));
    if (!newInterval) {
        printf("MALLOC FAILED IN interfaceUpdateReservation");
        return;
    }

    printf("\n*******> current interval");
    askForInterval(current);

    printf("\n***************><***************");
    int id = getUserNumber("\n enter your new id: ");
    char *description = getUserString("\n enter your new description: ");

    printf("\n*******> new interval");
    askForInterval(newInterval);

    updateReservation(tree, current, newInterval, id, description);
}

void interfaceDeletereservaion(Tree *tree) {
    Interval *current = malloc(sizeof(Interval));
    if (!current) {
        printf("MALLOC FAILED IN interfaceDeletereservaion");
        return;
    }

    askForInterval(current);

    deleteReservation(tree, current);
}

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

void exportTreeToCSV(const Tree tree, FILE *file) {
    if (!tree)
        return;

    exportTreeToCSV(tree->left, file);

    fprintf(file, "%d,%s,%d,%d\n",
            tree->id,
            tree->description,
            tree->interval->start,
            tree->interval->end);

    exportTreeToCSV(tree->right, file);
}

void interfaceImportData(Tree *tree) {
    char *filename = getUserString("Enter a path to TP4_interval.txt file:");

    FILE *file = fopen(strcat(filename, "\\TP4_reservation.txt"), "r");
    if (!file) {
        printErrorTreeMessages("Error opening file.\nThe file might not exist or the path is wrong");
        return;
    }

    char line[MAX_BUFFER_SIZE];
    int id, start, end;
    char description[128];

    fgets(line, sizeof(line), file); // ignore the first line in the CSV (it is the description format)

    while (fgets(line, sizeof(line), file))
        if (sscanf(line, "%d,%127[^,],%d,%d", &id, description, &start, &end) == 4)
            addReservation(tree, id, createInterval(start, end), description);

    fclose(file);
}

void interfaceExportData(const Tree tree) {
    char *filename = getUserString("Enter a directory:");

    FILE *file = fopen(strcat(filename, "\\TP4_reservation.txt"), "w");
    if (!file) {
        printErrorTreeMessages("Error opening file.\nThe file might not exist or the path is wrong");
        return;
    }

    fprintf(file, "Formated data: ID, Description, Start, End\n");

    exportTreeToCSV(tree, file);

    fclose(file);
}

void interfaceShowyCompaniesReservation(const Tree tree) {
    int nb = nbNodes(tree);
    int *nb_company = malloc(sizeof(int));
    *nb_company = 0;
    int **mat = (int **) malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        mat[i] = (int *) malloc(nb * sizeof(int));
    }
    for (int i = 0; i < nb; i++) {
        mat[0][i] = mat[1][i] = 0;
    }

    nbReservationByCompany(tree, mat, nb_company);
    printf("\n-----------------------> COMPANIES NUMBER OF RESERVATIONS <-------------");
    for (int i = 0; i < *nb_company; i++) {
        printf("\n--> company:  %d -- reservation(s) : %d \t", mat[0][i], mat[1][i]);
    }
    printf("\n------------------------------------------------------------------------\n");

    free(nb_company);
    for (int i = 0; i < 2; ++i)
        free(mat[i]);
    free(mat);
}
