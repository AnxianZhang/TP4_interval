//
// Created by gadan on 12/5/2024.
//

#ifndef NODE_H
#define NODE_H

#include "Interval.h"

typedef struct Node {
    unsigned int id;
    char *description;
    Interval *interval;
    struct Node *right;
    struct Node *left;
} Node;

typedef Node *Tree;

Node *createNode(unsigned int id, char *description, Interval *interval);

void addReservation(Tree tree, unsigned int id, Interval *interval, char *description);

Node *searchReservation(const Tree tree, const Interval *interval, unsigned int id);

void deleteReservation(Tree tree, Interval *interval, unsigned int id);

void updateReservation(Tree tree, Interval *current, Interval *newInterval, unsigned int id);

char *getParsedDate(unsigned int date);

void showTree(const Tree tree);

int isIdPresent(const Tree tree, unsigned int id);

int isIntervalContainingReservation(const Tree tree, const Interval *period);

void showCompany(const Tree tree, unsigned int id);

void showPeriod(const Tree tree, const Interval *period);

void deleteAll(Tree tree);

int comparator(int a, int b);
#endif //NODE_H
