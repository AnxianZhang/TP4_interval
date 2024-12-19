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

/**
 * Create new node with the given parameters
 * @param id
 * @param description
 * @param interval
 * @return
 */
Node *createNode(unsigned int id, char *description, Interval *interval);

/**
 * Add a new reservation
 * @param tree
 * @param id
 * @param interval
 * @param description
 * @return
 */
int addReservation(Tree *tree, unsigned int id, Interval *interval, char *description);

/**
 * search a specific reservation
 * @param tree
 * @param interval
 * @return
 */
Node *searchReservation(const Tree tree, const Interval *interval);

/**
 * Delete a reservation through th provided interval
 * @param tree
 * @param interval
 */
void deleteReservation(Tree *tree, Interval *interval);

/**
 * Update a reservation, the id, interval and description, can be modifed
 * @param tree
 * @param current old interval use to search the Node
 * @param newInterval
 * @param id
 * @param description
 */
void updateReservation(Tree *tree, Interval *current, Interval *newInterval, int id, char *description);

/**
 * Through the provided date, it formated to DD/MM/YYYYY
 * @param date 
 * @return 
 */
char *getParsedDate(unsigned int date);

/**
 * Show all reservation
 * @param tree
 */
void showTree(const Tree tree);

/**
 * Show all reservation of the specific company id
 * @param tree
 * @param id
 * @return
 */
int showCompany(const Tree tree, unsigned int id);

/**
 * Show all reservation within a provided interval
 * @param tree
 * @param period
 * @return 1 if the tree isn't empty, 0 else
 */
int showPeriod(const Tree tree, const Interval *period);

/**
 * Free all nodes in the tree
 * @param tree
 */
void deleteAll(Tree tree);

/**
 * Compare 2 dates
 * @param a first date
 * @param b second date
 * @return 1 if a is in the right of b
 *         0 if a is in the left of b
 *        -1 if both are the same
 */
int comparatorDate(unsigned int a, unsigned int b);
#endif //NODE_H
