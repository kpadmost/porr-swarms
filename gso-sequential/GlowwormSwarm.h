//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORMSWARM_H
#define PORR_SWARMS_GLOWWORMSWARM_H

#include "Glowworm.h"

namespace gso {
    class GlowwormSwarm {
    private:
        // members
        std::vector<Glowworm> population;
        const Parameters parameters;

        // main steps
        void movement(); // move glowworms
        void updateLuciferine(); // update luciferine
        void neighbourhoodRangeUpdate();

    public:
        void runAlgorithm();

        GlowwormSwarm(std::function<float(Position)> function) : parameters(function) { }
    };
}

#endif //PORR_SWARMS_GLOWWORMSWARM_H
