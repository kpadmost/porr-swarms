//
// Created by Konstantin on 08.12.2019.
//

#include "Glowworm.h"

void gso::Glowworm::updateLuciferin() {
    const auto ro = pParameters->ro;
    const auto gamma = pParameters->gamma;
    const auto costFunction = pParameters->consFunction;
    luciferin = (1 - ro) * luciferin + gamma * costFunction(this->position);
}
