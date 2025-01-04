//
// Created by anxian and bryan on 12/5/2024.
//

#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct Interval {
    unsigned int start;
    unsigned int end;
} Interval;

Interval *createInterval(int start, int end);

#endif //INTERVAL_H
