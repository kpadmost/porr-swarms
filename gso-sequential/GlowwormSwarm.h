//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORMSWARM_H
#define PORR_SWARMS_GLOWWORMSWARM_H


#include <cmath>
#include <iostream>

#include "Random.hpp"
#include "Glowworm.h"
using namespace std;

namespace gso {
    class GlowwormSwarm {
    private:
        // members
        std::vector<Glowworm> population;
        Parameters parameters;

        // main steps
        void movePopulation(); // move glowworms
        void updateLuciferine(); // update luciferine
        void neighbourhoodRangeUpdate(Glowworm& worm, const size_t neighboursNumber);

        unsigned int selectWormFromProbability(const std::vector<double>& probabilities);
        void initializeAlgorithm();
    public:
        void runAlgorithm();
        Position getBestWorm();
        GlowwormSwarm(
                const std::function<float(const Position&)> &function,
                unsigned int iterationNumber, float rs, size_t populationN, unsigned int dimensions
        ) : parameters(function, iterationNumber, rs, populationN,dimensions) { }
    };


}

#endif //PORR_SWARMS_GLOWWORMSWARM_H
