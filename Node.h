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

int addReservation(Tree *tree, unsigned int id, Interval *interval, char *description);

Node *searchReservation( Tree tree, Interval *interval);

void deleteReservation(Tree *tree, Interval *interval);

void updateReservation(Tree *tree, Interval *current, Interval *newInterval, int id , char *description);

char *getParsedDate(unsigned int date);

void showTree(const Tree tree);

int isIdPresent(const Tree tree, unsigned int id);

int isIntervalContainingReservation(const Tree tree, const Interval *period);

int showCompany(const Tree tree, unsigned int id);

int showPeriod(const Tree tree, const Interval *period);

void deleteAll(Tree tree);

int comparatorDate(unsigned int a, unsigned int b);
#endif //NODE_H
