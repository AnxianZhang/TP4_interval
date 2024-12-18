//
// Created by ZHANG ANXIAN AND MIGUEU BRYAN on 12/5/2024.
//

#include "Node.h"
#include "Interfaces.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interval.h"

int comparatorDate(unsigned int a, unsigned int b) {
    if (a / 100 > b / 100)
        return 1;

    if (a / 100 == b / 100) {
        if (a % 100 > b % 100)
            return 1;
        if (a % 100 < b % 100)
            return 0;
        return -1;
    }
    return 0;
}

int comparatorInteval(const Interval *a, const Interval *b) {
    if (comparatorDate(a->start, b->start) == -1 && comparatorDate(a->end, b->end) == -1)
        return -1;
    return 0;
}

Node *searchReservation(const Tree tree, const Interval *interval) {
    if (tree == NULL)
        return NULL;
    Node *node = tree;
    while (node && comparatorInteval(node->interval, interval) != -1) {
        if (comparatorDate(node->interval->start, interval->end) == 1)
            node = node->left;
        else if (comparatorDate(node->interval->end, interval->start) == 0)
            node = node->right;
        else
            return NULL;
    }
    return node;
}

Node *createNode(unsigned int id, char *description, Interval *interval) {
    if (!interval) return NULL;

    Node *n = malloc(sizeof(Node));
    if (!n) {
        printf("MALLOC FAILED IN createNode");
        return NULL;
    }

    n->id = id;
    n->description = malloc(sizeof(char) * strlen(description));

    if (!n->description) {
        free(n);
        printf("MALLOC FAILED IN createNode");
        return NULL;
    }

    strcpy(n->description, description);
    n->interval = interval;
    n->left = NULL;
    n->right = NULL;

    return n;
}

int addReservation(Tree *tree, unsigned int id, Interval *interval, char *description) {
    if (*tree == NULL) {
        *tree = createNode(id, description, interval);
        return 1;
    }
    Node *test_node = searchReservation(*tree, interval);
    int add;

    if (!test_node) {
        int test = 0;
        Node *node = createNode(id, description, interval);
        Node *p = *tree;
        Node *q = *tree;
        while (p) {
            q = p;
            if (comparatorDate(p->interval->start, interval->end) == 1)
                p = p->left;
            else if (comparatorDate(p->interval->end, interval->start) == 0)
                p = p->right;
            else {
                test = 1;
                p = NULL; // to out of the loop
            }
        }
        if (test == 1) {
            printf("interval invalide\n");
            add = 0;
        } else {
            if (comparatorDate(q->interval->start, interval->end) == 1)
                q->left = node;
            if (comparatorDate(q->interval->end, interval->start) == 0)
                q->right = node;
            add = 1;
        }
    } else {
        printf("resavation unavailable \n");
        add = 0;
    }
    return add;
}

void *father(Tree tree, Node *node) {
    if (tree && node) {
        Node *p = tree;
        Node *q = tree;
        if (p == node)
            return NULL;
        int test = 1;
        while (p != node) {
            q = p;
            if (comparatorDate(p->interval->start, node->interval->end) == 1)
                p = p->left;
            else if (comparatorDate(p->interval->end, node->interval->start) == 0)
                p = p->right;
            else {
                test = 0;
                p = NULL; // to out of the loop
            }
        }
        if (test == 1)
            return q;
        // p = NULL
        return p;
    }
}

Node *successor(Tree tree, Tree node) {
    if (tree) {
        Node *p;
        if (node->right) {
            p = node->right;
            while (p->left) {
                p = p->left;
            }
            return p;
        }

        p = node;
        Node *pere = father(tree, p);
        while (p && pere->right == p) {
            p = pere;
            pere = father(tree, pere);
        }
        return pere;
    }
}

void deleteReservation(Tree *tree, Interval *interval) {
    if (tree && interval) {
        Node *node = searchReservation(*tree, interval);
        if (node) {
            Node *p = father(*tree, node);
            if (p) {
                if (!node->left && !node->right) {
                    if (p->left == node)
                        p->left = NULL;
                    if (p->right == node)
                        p->right = NULL;
                    free(node->description);
                    free(node->interval);
                    free(node);
                } else if (!node->right && node->left) {
                    if (p->left == node)
                        p->left = node->left;
                    if (p->right == node)
                        p->right = node->left;
                    free(node->description);
                    free(node->interval);
                    free(node);
                } else if (!node->left && node->right) {
                    if (p->left == node)
                        p->left = node->right;
                    if (p->right == node)
                        p->right = node->right;
                    free(node->description);
                    free(node->interval);
                    free(node);
                } else {
                    Node *suc = successor(*tree, node);
                    char *description = suc->description;
                    int id = suc->id;
                    Interval *i = suc->interval;
                    deleteReservation(tree, (suc->interval));
                    node->description = description;
                    node->id = id;
                    node->interval = i;
                }
            } else {
                if (!node->left && !node->right) {
                    free(node->description);
                    free(node->interval);
                    node->description = NULL;
                    node->interval = NULL;
                    *tree = NULL;
                } else {
                    Node *suc = successor(*tree, node);
                    char *description = suc->description;
                    int id = suc->id;
                    Interval *i = suc->interval;
                    deleteReservation(tree, (suc->interval));
                    node->description = description;
                    node->id = id;
                    node->interval = i;
                }
            }
        } else
            printErrorTreeMessages("\n this reservation does not exist ");
    }
}

void updateReservation(Tree *tree, Interval *current, Interval *newInterval, int id, char *description) {
    if (tree && current && newInterval) {
        Node *node = searchReservation(*tree, current);
        if (node) {
            deleteReservation(tree, node->interval);
            int add = addReservation(tree, id, newInterval, description);
            if (add == 0) {
                // if add don't work
                free(newInterval);
                addReservation(tree, id, current, description);
            } else
                free(current);
        } else
            printf("resavation unavailable \n");
    }
}

void extractSubString(char *src, char *dest, unsigned int start, unsigned int length) {
    strncpy(dest, src + start, length);
    dest[length] = '\0';
}

char *getParsedDate(unsigned int date) {
    char *formatedDate = malloc(sizeof(char) * 15);
    if (!formatedDate) {
        printf("MALLOC FAILED IN getParsedDate");
        return NULL;
    }

    unsigned int month = date / 100;
    unsigned int day = date % 100;

    char *cMonth = (month < 10 ? "0" : "");
    char *cDay = (day < 10 ? "0" : "");


    sprintf(formatedDate, "%s%d/%s%d/2024", cDay, day, cMonth, month);

    return formatedDate;
}

void showTree(const Tree tree) {
    if (!tree) return;
    showTree(tree->left);

    char *startDate = getParsedDate(tree->interval->start);
    char *endDate = getParsedDate(tree->interval->end);

    printf("%s to %s : company %-3d - %s \n", startDate, endDate, tree->id, tree->description);

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

int showCompany(const Tree tree, unsigned int id) {
    if (!tree) return 0;

    int leftFlag = showCompany(tree->left, id);

    int currentFlag = 0;
    if (tree->id == id) {
        char *startDate = getParsedDate(tree->interval->start);
        char *endDate = getParsedDate(tree->interval->end);

        printf("%s to %s : company %-3d - %s \n", startDate, endDate, tree->id, tree->description);

        free(startDate);
        free(endDate);

        currentFlag = 1;
    }

    int rightFlag = showCompany(tree->right, id);

    return leftFlag || currentFlag || rightFlag;
}

int showPeriod(const Tree tree, const Interval *period) {
    if (!tree) return 0;


    int leftFlag = showPeriod(tree->left, period);
    int currentFlag = 0;

    if ((tree->interval->start >= period->start && tree->interval->start <= period->end) ||
        (tree->interval->end >= period->start && tree->interval->end <= period->end)) {
        char *startDate = getParsedDate(tree->interval->start);
        char *endDate = getParsedDate(tree->interval->end);

        printf("%s to %s : company %-3d - %s \n", startDate, endDate, tree->id, tree->description);

        free(startDate);
        free(endDate);

        currentFlag = 1;
    }

    int rightFlag = showPeriod(tree->right, period);
    return currentFlag || leftFlag || rightFlag;
}

void deleteAll(Tree tree) {
    if (!tree) return;

    deleteAll(tree->left);
    deleteAll(tree->right);

    free(tree->description);
    free(tree->interval);

    free(tree);
}
