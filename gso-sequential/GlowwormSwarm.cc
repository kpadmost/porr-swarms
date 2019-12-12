//
// Created by Konstantin on 08.12.2019.
//

#include <algorithm>
#include "GlowwormSwarm.h"
#include "Glowworm.h"

void gso::GlowwormSwarm::updateLuciferine() {
    const float ro = parameters.ro;
    const float gamma = parameters.gamma;
    const auto costFunction = parameters.consFunction;
    for(auto a = population.begin(); a != population.end(); a++) {
        a->luciferin = (1 - ro) * a->luciferin - gamma * costFunction(a->position);
    }
}

void gso::GlowwormSwarm::movePopulation() {
    // for each worm
    for(auto worm = population.begin(); worm != population.end(); worm++) {
        // determine neighbourhood
        std::vector<gso::Glowworm> neighbours;

        for(auto oWorm = population.begin(); oWorm != population.end(); oWorm++)
            if(worm->distance(*oWorm) < worm->neighbourhoodRange && worm->luciferin < oWorm->luciferin)
                neighbours.push_back(*oWorm);
        // calculate probabilities
        if(neighbours.empty())
            continue;
        std::vector<double> probabilities(neighbours.size(), 0.0);
        double denominator = 0.0;
        for(auto oWorm = neighbours.begin(); oWorm != neighbours.end(); oWorm++)
            denominator += oWorm->luciferin - worm->luciferin;
        for(unsigned int i = 0; i < neighbours.size(); i++)
            probabilities[i] = (neighbours[i].luciferin - worm->luciferin) / denominator;
        // select worm based on probabilities

        const size_t wormIndex = selectWormFromProbability(probabilities);
        gso::Glowworm& chosenWorm = neighbours[wormIndex];
        // move towards that worm
        worm->moveTowardsWorm(chosenWorm, parameters.s);

        // neighbourhoodRangeUpdate
        neighbourhoodRangeUpdate(*worm, neighbours.size());
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
    const double p = Random<double>::getFromRange(0.0, 1.0);
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

void gso::GlowwormSwarm::runAlgorithm() {
    initializeAlgorithm();
    auto bp = getBestWorm();
    std::cout << "Iteration " << parameters.getT() << " cf " << parameters.consFunction(bp) << std::endl;
    std::for_each(bp.begin(), bp.end(), [] (const auto &d) {std::cout << d << " ";});
    std::cout << std::endl;
    while(parameters.getT() < parameters.maxT) {
        updateLuciferine();
        movePopulation();
        parameters.updateT();
        auto bp = getBestWorm();
        std::cout << "Iteration " << parameters.getT() << " cf " << parameters.consFunction(bp) << " ";
        std::for_each(bp.begin(), bp.end(), [] (const auto &d) {std::cout << d << " ";});
        std::cout << std::endl;
    }

}

Position gso::GlowwormSwarm::getBestWorm() {
    // TODO : change to loop
    Glowworm g = population[0];
    for(auto i = population.begin(); i != population.end(); i++) {
        if(parameters.consFunction(i->position) < parameters.consFunction(g.position))
            g = *i;
    }
    return g.position;
}

inline void gso::GlowwormSwarm::neighbourhoodRangeUpdate(gso::Glowworm &worm, const size_t neighboursNumber) {
    const float beta = parameters.beta;
    const float nt = parameters.nt;
    const float ri = worm.neighbourhoodRange;
    worm.neighbourhoodRange = std::fmax(parameters.rs, std::fmax(0.0f, ri + beta * (nt - neighboursNumber)));
}

void gso::GlowwormSwarm::initializeAlgorithm() {
    // initialize population
    const auto m = parameters.dimensions;
    const auto l0 = parameters.l0;
    const auto rs = parameters.rs;
    for(int i = 0; i < parameters.populationNumber; i++) {
        //TODO change constraint
        population.emplace_back(Glowworm(m, l0, rs));
    }

}
