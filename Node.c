//
// Created by Bryan on 12/7/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interval.h"
#include "Node.h"

/*
 *NB a et b sont des dates
 * comparator retoune 1 si a est a droite de b
 *                     0 si a est a gauche d eb
 *                    -1 si les deux dates sont pareille
 */
int comparator(int a, int b) {
    if (a / 100 > b / 100)
        return 1;
    else {
        if (a / 100 == b / 100) {
            if (a % 100 > b % 100)
                return 1;
            if (a / 100 < b % 100)
                return 0;
            return -1;
        } else
            return 0;
    }
}

Node *searchReservation(const Tree tree, const Interval *interval, unsigned int id) {
    Node *node = tree;
    while (node->id != id && node) {
        if (comparator(node->interval->start, interval->end) == 1)
            node = node->left;
        if (comparator(node->interval->end, interval->start) == 0)
            node = node->right;
    }
    return node;
}

void addReservation(Tree tree, unsigned int id, Interval *interval, char *description) {
    if(!searchReservation(tree,interval,id)) {
        int test=0;
        Node *node = createNode(id, description,interval);
        Node *p=tree;
        Node *q=tree;
        while(p) {
            q=p;
            if(comparator(p->interval->start,interval->end)==1)
                p=p->left;
            else if(comparator(p->interval->end,interval->start)==0)
                p=p->right;
            else {
                test=1;
                p=NULL; // to out of the loop
            }
        }
        if(test==1)
            printf("interval invalide\n");
        else {
            if(comparator(q->interval->start,interval->end)==1)
                q->left=node;
            if(comparator(q->interval->end,interval->start)==0)
                q->right=node;
        }
    }
    else
        printf("resavation unavailable \n");
}

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

int isIdPresent(const Tree tree, unsigned int id) {
    if (!tree) return 0;

    if (tree->id == id)
        return 1;

    if (isIdPresent(tree->left, id))
        return 1;

    return isIdPresent(tree->right, id);
}

int isIntervalContainingReservation(const Tree tree, const Interval *period) {
    if (!tree) return 0;

    if ((tree->interval->start >= period->start && tree->interval->start <= period->end) ||
        (tree->interval->end >= period->start && tree->interval->end <= period->end))
        return 1;

    if (isIntervalContainingReservation(tree->left, period))
        return 1;

    return isIntervalContainingReservation(tree->right, period);
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

void deleteAll(Tree tree) {
    if (!tree) return;

    deleteAll(tree->left);
    deleteAll(tree->right);

    free(tree->description);
    free(tree->interval);

    free(tree);
}
