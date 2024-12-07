//
// Created by gadan on 12/6/2024.
//

#include "Interfaces.h"

#include <stdio.h>

#include "Utile.h"

int hasTreeAndLeftRight(const Tree tree) {
    return tree != NULL && tree->left != NULL && tree->right != NULL;
}

void printErrorTreeMessages(const char *specificMessage) {
    printf("%s\n", specificMessage);
    printf("Please try again later\n");
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
