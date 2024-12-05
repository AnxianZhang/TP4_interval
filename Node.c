//
// Created by Bryan on 12/5/2024.
//

#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extractSubString(char *src, char *dest, unsigned int start, unsigned int length) {
    strncpy(dest, src + start, length);
    dest[length] = '\0';
}

char *getParsedDate(unsigned int date) {
    char buffer[20] = "", day[3] = "", month[3] = "";
    sprintf(buffer, "%d", date);
    char *formatedDate = malloc(sizeof(char) * 15);

    if (!formatedDate) return NULL;

    if (strlen(buffer) == 3) {
        snprintf(month, sizeof(month), "0%c", buffer[0]);
        extractSubString(buffer, day, 1, 2);
    } else {
        extractSubString(buffer, month, 0, 2);
        extractSubString(buffer, day, 2, 2);
    }

    snprintf(formatedDate, 15, "%s/%s/2024", day, month);

    return formatedDate;
}

Node *createNode(unsigned int id, char *description, Interval *interval) {
    if (!interval) return NULL;

    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;

    n->id = id;
    n->description = malloc(sizeof(char) * strlen(description));

    if (!n->description) {
        free(n);
        return NULL;
    }

    strcpy(n->description, description);
    n->interval = interval;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void showTree(const Tree tree) {
    if (!tree) return;
    showTree(tree->left);

    char *startDate = getParsedDate(tree->interval->start);
    char *endDate = getParsedDate(tree->interval->end);

    printf("%s to %s : company %d - %s \n", startDate, endDate, tree->id, tree->description);

    free(startDate);
    free(endDate);

    showTree(tree->right);
}

void showCompany(const Tree tree, unsigned int id) {
    if (!tree) return;
    showCompany(tree->left, id);

    if (tree->id == id) {
        char *startDate = getParsedDate(tree->interval->start);
        char *endDate = getParsedDate(tree->interval->end);

        printf("%s to %s : company %d - %s \n", startDate, endDate, tree->id, tree->description);

        free(startDate);
        free(endDate);
    }

    showCompany(tree->right, id);
}

void showPeriod(const Tree tree, const Interval *period) {
    if (!tree) return;
    showPeriod(tree->left, period);

    if ((tree->interval->start >= period->start && tree->interval->start <= period->end) ||
        (tree->interval->end >= period->start && tree->interval->end <= period->end)) {
        char *startDate = getParsedDate(tree->interval->start);
        char *endDate = getParsedDate(tree->interval->end);

        printf("%s to %s : company %d - %s \n", startDate, endDate, tree->id, tree->description);

        free(startDate);
        free(endDate);
    }

    showPeriod(tree->right, period);
}

void freeAllNodes(const Tree tree) {
}

void deleteAllFree(Tree tree) {
    if (!tree) return;
    deleteAllFree(tree->left);
    deleteAllFree(tree->right);

    printf("umh\n");

    free(tree->description);
    free(tree->interval);

    free(tree);
}
