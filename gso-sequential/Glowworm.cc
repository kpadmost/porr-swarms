//
// Created by Konstantin on 08.12.2019.
//
#include <algorithm>

#include "Glowworm.h"

void gso::Glowworm::updateLuciferin() {


}

void gso::Glowworm::move(const std::vector<const gso::Glowworm> &population) {

}

float gso::Glowworm::distance(const gso::Glowworm &other) const {
    const Position& oPos = other.position;
    float distance = 0.0;
    for(auto a = position.begin(), b = oPos.begin(); a!= position.end(); a++, b++)
        distance += pow(*a - *b, 2);
    return sqrt(distance);
}
