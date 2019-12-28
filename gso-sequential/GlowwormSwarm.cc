//
// Created by Konstantin on 08.12.2019.
//

#include <algorithm>
#include "GlowwormSwarm.h"
#include "Glowworm.h"

void gso::GlowwormSwarm::updateLuciferine() {
    const float ro = parameters.ro;
    const float gamma = parameters.gamma;
    const auto costFunction = parameters.costFunction;
    const int size = population.size();

    for(int i = 0; i < size; i++) {
        //Glowworm& a = population[i];
        population[i].luciferin = (1 - ro) * population[i].luciferin - gamma * costFunction(population[i].position, p);
    }
}

void gso::GlowwormSwarm::movePopulation() {
    // for each worm
    const int size = population.size();

    for (int i = 0; i < size; i++) { // P
        Glowworm &worm = population[i];
        // determine neighbourhood
        std::vector<gso::Glowworm> neighbours;

        for (int j = 0; j < population.size(); j++) {
            Glowworm oWorm = population[j];
            if (worm.distance(oWorm) < worm.neighbourhoodRange && worm.luciferin < oWorm.luciferin)
                neighbours.push_back(oWorm);
        }
        // calculate probabilities
        if (neighbours.empty())
            continue;
        std::vector<double> probabilities(neighbours.size(), 0.0);
        double denominator = 0.0;
        for (auto oWorm = neighbours.begin(); oWorm != neighbours.end(); oWorm++)
            denominator += oWorm->luciferin - worm.luciferin;
        for (unsigned int k = 0; k < neighbours.size(); k++)
            probabilities[k] = (neighbours[k].luciferin - worm.luciferin) / denominator;
        // select worm based on probabilities

        const size_t wormIndex = selectWormFromProbability(probabilities);
        gso::Glowworm &chosenWorm = neighbours[wormIndex];
        // move towards that worm
        worm.moveTowardsWorm(chosenWorm, parameters.s);

        // neighbourhoodRangeUpdate
        neighbourhoodRangeUpdate(worm, neighbours.size());
    }

}

unsigned int gso::GlowwormSwarm::selectWormFromProbability(const std::vector<double> &probabilities) {
    if(probabilities.size() == 1)
        return 0;
    std::vector<double> accumulatedProbabilities(probabilities.size(), 0.0);
    accumulatedProbabilities[0] = probabilities[0];
    for(size_t i = 1; i < probabilities.size(); i++)
        accumulatedProbabilities[i] = accumulatedProbabilities[i - 1] + probabilities[i];
    // randomly select
    const double p = random.getFromRange(0.0, 1.0);

    // binary search
    int l = 0, h = accumulatedProbabilities.size() - 1, mid = (h + l) / 2;
    while(l <= h && h >= 0) {
        if(accumulatedProbabilities[mid] < p)
            l = mid + 1;
        else
            h = mid - 1;
        mid = (l + h) / 2;
    }
    return mid + 1;
}

void gso::GlowwormSwarm::runAlgorithm(int t) {
    initializeAlgorithm();
    auto bp = getBestWorm();
//    std::cout << "Iteration " << 0 << " cf " << parameters.costFunction(bp, p) << std::endl;
    for(int i = 0; i < t; i++) {
        updateLuciferine(); // run in parallel for population
        //block
        movePopulation(); // run in parallel for population
        //block
        bp = getBestWorm();
        //    std::cout << "Iteration " << i << " p " << p << " cf " << parameters.costFunction(bp, p) << std::endl;
        p = p + 100;
    }


}

gso::Position gso::GlowwormSwarm::getBestWorm() const {
    // TODO : change to loop
    gso::Glowworm g = population[0];
    for(size_t i = 1; i < population.size(); i++) {
        const Glowworm other = population[i];
        if(parameters.costFunction(other.position, p) < parameters.costFunction(g.position, p))
            g = other;
    }
    return g.position;
}

inline void gso::GlowwormSwarm::neighbourhoodRangeUpdate(gso::Glowworm &worm, const size_t neighboursNumber) {
    const float beta = parameters.beta;
    const int nt = parameters.nt;
    const float ri = worm.neighbourhoodRange;
    worm.neighbourhoodRange = std::fmin(parameters.rs, std::fmax(0.0f, ri + beta * (nt - neighboursNumber)));
}

void gso::GlowwormSwarm::initializeAlgorithm() {
    // initialize population
    const auto m = parameters.dimensions;
    const auto l0 = parameters.l0;
    const auto rs = parameters.rs;
    for(size_t i = 0; i < parameters.populationNumber; i++) {
        //TODO change constraint
        population.emplace_back(m, l0, rs, random);
    }

}
