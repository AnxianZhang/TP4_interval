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

void addReservation(Tree *tree, unsigned int id, Interval *interval, char *description);

Node *searchReservation(const Tree *tree, Interval *interval, unsigned int id);

void deleteReservation(Tree *tree, Interval *interval, unsigned int id);

void updateReservation(Tree *tree, Interval *current, Interval *newInterval, unsigned int id);

void showTree(const Tree tree);

void showCompany(const Tree tree, unsigned int id);

void showPeriod(const Tree *tree, const Interval *period);

void deleteAllFree(const Tree *tree);

#endif //NODE_H
