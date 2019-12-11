//
// Created by Konstantin on 08.12.2019.
//
#include <algorithm>

#include "Glowworm.h"


float gso::Glowworm::distance(const gso::Glowworm &other) const {
    const Position& oPos = other.position;
    float distance = 0.0;
    for(auto a = position.begin(), b = oPos.begin(); a!= position.end(); a++, b++)
        distance += pow(*a - *b, 2);
    return sqrt(distance);
}

void gso::Glowworm::moveTowardsWorm(const gso::Glowworm& other, float step) {
    // calculate result position
    const Position& oPosition = other.position;
    const size_t size = position.size();
    Position result(oPosition.size());
    for(size_t i = 0; i < size; i++) {
        result[i] = oPosition[i] - position[i];
    }
    // calculate euclidean norm
    float norm = 0.0;
    for(size_t i = 0; i < size; i++) {
        norm += result[i] * result[i];
    }
    norm = sqrt(norm);
    // adjust position
    for(size_t i = 0; i < size; i++) {
        position[i] = position[i] +  (step / norm) * result[i];
    }
}

void gso::Glowworm::initializePosition(const size_t m) {
    for(size_t i = 0; i < m; i++) // TODO: change constraint
        position.push_back(Random<float>::getFromRange(-40.0f, 40.0f));


}
