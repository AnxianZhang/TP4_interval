//
// Created by gadan on 12/6/2024.
//

#ifndef INTERFACES_H
#define INTERFACES_H

#include "Node.h"

void printErrorTreeMessages(const char *specificMessage);

void interfaceShowTree(const Tree tree);

void interfaceShowCompany(const Tree tree);

void interfaceShowPeriod(const Tree tree);

void interfaceAddreservation(Tree *tree);

void interfaceUpdateReservation( Tree *tree);

void interfaceDeletereservaion(Tree* tree);

void interfaceSearchReservation(const Tree tree);
#endif //INTERFACES_H
