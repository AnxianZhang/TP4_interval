//
// Created by gadan on 12/6/2024.
//

#include "Interfaces.h"

#include <stdio.h>

#include "Utile.h"

#include "Node.h"

#include "interval.h"

int hasTreeAndLeftRight(const Tree tree) {
    return tree != NULL && tree->left != NULL && tree->right != NULL;
}

void printErrorTreeMessages(const char *specificMessage) {
    printf("%s\n", specificMessage);
    printf("Please try again later\n");
}
void printErrorMessages(const char *specificMessage) { // it's for bryan
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
        char messageBuffer[BUFFER_MAX_SIZE + 1] = {""};

        snprintf(messageBuffer, BUFFER_MAX_SIZE + 1, "The company number %d haven't make reservation !", id);
        printErrorTreeMessages(messageBuffer);
    }
}

void interfaceShowPeriod(const Tree tree) {
    Interval i;
    i.start = getUserNumber("Enter the start of the period:");
    i.end = getUserNumber("Enter the end of the period:");

    if (!hasTreeAndLeftRight(tree)) {
        printEmptyTreeMessages();
        return;
    }

    if (!showPeriod(tree, &i)) {
        char *startDateBuffer = getParsedDate(i.start);
        char *endDateBuffer = getParsedDate(i.end);
        char messageBuffer[BUFFER_MAX_SIZE + 1] = {""};

        snprintf(
            messageBuffer,BUFFER_MAX_SIZE + 1,
            "There are no reservation in the period of %s to %s !",
            startDateBuffer, endDateBuffer
        );
        printErrorTreeMessages(messageBuffer);
    }
}
int numberOfDaysInMonth(int month) {
    if (month == 2)
        return 29;
    if (month <= 7)
        return 30+month%2;
    else
        return 31-month%2;
}

int getUserValideDate(){
    int month,day;
    month=getUserNumber("\nenter the number of your month: ");
    while (month < 1 || month > 12) {
        printErrorTreeMessages("\nIncorrect month number entered");
        month=getUserNumber("\nenter the number of your month: ");
    }
    day=getUserNumber("\nenter the number of your day: ");
    while (day < 1 || day > numberOfDaysInMonth(month)) {
        printErrorTreeMessages("\nIncorrect day number entered");
        day=getUserNumber("\nenter the number of your day: ");
    }
    return month*100+day;
}

void interfaceAddreservation(const Tree tree) {
    int id = getUserNumber("\nWhich id reservation you want to add ?: ");
    Interval interval;
    char *description;
    printf("\n******** start date");
    interval.start = getUserValideDate();
    printf("\n******** end date");
    interval.end = getUserValideDate();
    while (comparatorDate(interval.end, interval.start)!=1) {
        printErrorTreeMessages("\n end must be after start");
        interval.end = getUserValideDate();
    }
    description= getUserString("\nDescription reservation you want to add : ");
    addReservation(tree, id, &interval, description);
}
void interfaceUpdateReservation(const Tree tree) {
    int id = getUserNumber("\nWhich id reservation you want to update ?: ");
    Interval current, newInterval;

    printf("\n******** start date of current interval");
    current.start = getUserValideDate();
    printf("\n******** end date of current interval");
    current.end = getUserValideDate();
    while (comparatorDate(current.end, current.start)!=1) {
        printErrorTreeMessages("\n end must be after start");
        current.end = getUserValideDate();
    }

    printf("\n******** start date of new interval");
    newInterval.start = getUserValideDate();
    printf("\n******** end date of newI interval");
    newInterval.end = getUserValideDate();
    while (comparatorDate(newInterval.end, newInterval.start)!=1) {
        printErrorTreeMessages("\n end must be after start");
        newInterval.end = getUserValideDate();
    }

    updateReservation(tree, &current, &newInterval, id);
}
 void interfaceDeletereservaion(const Tree tree) {
    int id=getUserNumber("\nWhich id reservation you want to delete ?: ");
    Interval current;
    printf("\n******** start date of current interval");
    current.start = getUserValideDate();
    printf("\n******** end date of current interval");
    current.end = getUserValideDate();
    while (comparatorDate(current.end, current.start)!=1) {
        printErrorTreeMessages("\n end must be after start");
        current.end = getUserValideDate();
    }
    deleteReservation(tree, &current, id);
}

void interfaceSearchReservation(const Tree tree) {
    int id=getUserNumber("\nWhich id reservation you want to search?: ");
    Interval current;
    printf("\n******** start date of current interval");
    current.start = getUserValideDate();
    printf("\n******** end date of current interval");
    current.end = getUserValideDate();
    while (comparatorDate(current.end, current.start)!=1) {
        printErrorTreeMessages("\n end must be after start");
        current.end = getUserValideDate();
    }
    Node *node=searchReservation( tree, &current, id);

    if(node) {
        char *startDate = getParsedDate(node->interval->start);
        char *endDate = getParsedDate(node->interval->end);

        printf("\n--------> votre reservation <-----------");
        printf("\n id: %d", node->id);
        printf("\nstart date :%s",startDate);
        printf("\nend date :%s",endDate);
        printf("\ndescription: %s", node->description);
        printf("\n----------------------------------------\n");
    }
    else {
        printErrorTreeMessages("\n votre reservation not found");
    }

}