//
// Created by gadan on 12/19/2024.
//
#include "Interval.h"

#include <stdio.h>
#include <stdlib.h>

Interval *createInterval(int start, int end) {
    Interval *interval = malloc(sizeof(Interval));
    if (!interval) {
        printf("MALLOC FAILED IN createInterval");
        return NULL;
    }
    interval->start = start;
    interval->end = end;
    return interval;
}
