//
// Created by Konstantin on 09.12.2019.
//

#include "GlowwormPopulation.h"

void gso::GlowwormPopulation::updateGlowwormLuciferine(gso::Glowworm& worm) { // for each
    const auto ro = parameters.ro;
    const auto gamma = parameters.gamma;
    const auto costFunction = parameters.consFunction;
    worm.luciferin = (1 - ro) * worm.luciferin + gamma * costFunction(worm.position);
    moveGlowworm(worm);
}

void gso::GlowwormPopulation::moveGlowworm(gso::Glowworm &gw) {
    std::vector<Glowworm&> neighbours;
    // get neighbours
    std::copy_if(population.begin(), population.end(),
                 neighbours.begin(), [&gw] (const auto &a) {
        return gw.distance(a) < gw.neighbourhoodRange && a.luciferin > gw.luciferin;
    });
    // calculate probabilities
    std::vector<double> probabilities(neighbours.size(), 0.0);
    const double denominator = std::accumulate(neighbours.begin(), neighbours.end(), 0.0, [&gw] (const auto &neighbour) {
        return neighbour.luciferin -  gw.luciferin;
    });
    for(int i = 0; i < probabilities.size(); i++) {
        probabilities[i] = neighbours[i].luciferin - gw.luciferin;
    }
    // select glowworm to move to

    // update neighbours range

}

/*void gso::GlowwormPopulation::moveGlowworm(gso::Glowworm& worm) {

    int a = 0;
    std::vector<gso::Glowworm> pops;



}*/

