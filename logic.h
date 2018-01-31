//
// Created by liquidcore7 on 30.01.18.
//

#ifndef LIFE_LOGIC_H
#define LIFE_LOGIC_H

#include <vector>
#include <cmath>
#include <zconf.h>
#include "field.h"

short count_neighbours(size_t i, size_t j, size_t dimension, std::vector<bool>& state)
{
    short count = 0;
    bool hasLeft = j > 0, hasRight = j < (dimension - 1),
            hasOver = i > 0, hasLower = i < (dimension - 1);

    if (hasLeft) {
        count += state[i * dimension + j - 1];
        if (hasLower)
            count += state[(i + 1) * dimension + j - 1];
        if (hasOver)
            count += state[(i - 1) * dimension + j - 1];
    }
    if (hasRight) {
        count += state[i * dimension + j + 1];
        if (hasLower)
            count += state[(i + 1) * dimension + j + 1];
        if (hasOver)
            count += state[(i - 1) * dimension + j + 1];
    }
    if (hasLower)
        count += state[(i + 1) * dimension + j];
    if (hasOver)
        count += state[(i - 1) * dimension + j];

    return count;
}

void next_population(std::vector<bool> &prev)
{
    const size_t size = std::sqrt(prev.size());

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            switch (count_neighbours(i, j, size, prev))
            {
                case 3:
                    prev[i * size + j] = true;
                case 2:
                    break;
                default:
                    prev[i * size + j] = false;
                    break;
            }
        }
    }
}


#endif //LIFE_LOGIC_H
