//
// Created by Bryan on 12/7/2024.
//

#include "Interval.h"
#include <stdlib.h>

Interval *createInterval(int start, int end) {
    Interval *interval = (Interval *)malloc(sizeof(Interval));
    interval->start = start;
    interval->end = end;
    return interval;
}
