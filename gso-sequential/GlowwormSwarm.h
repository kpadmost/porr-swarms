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
        Random<float> random;
        // main steps
        void movePopulation(); // move glowworms
        void updateLuciferine(); // update luciferine
        void neighbourhoodRangeUpdate(Glowworm& worm, const size_t neighboursNumber);


        // worm-only
        std::vector<float> calculateProbabilities(const std::vector<Glowworm>);
        unsigned int selectWormFromProbability(const std::vector<double>& probabilities);
        void initializeAlgorithm();
    public:
        void runAlgorithm(int t);
        Position getBestWorm() const;
        GlowwormSwarm(
                const std::function<float(const Position&)> &function,
                float rs, size_t populationN, unsigned int dimensions
        ) : parameters(function, rs, populationN,dimensions) { }
    };


}

#endif //PORR_SWARMS_GLOWWORMSWARM_H
