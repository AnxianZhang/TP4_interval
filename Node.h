//
// Created by gadan on 12/5/2024.
//

#ifndef NODE_H
#define NODE_H

#include "Interval.h"

typedef struct Node {
    Interval *interval;
    struct Node *right;
    struct Node *left;
} Node;

typedef Node *Tree;

#endif //NODE_H
