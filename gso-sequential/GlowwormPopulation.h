//
// Created by Konstantin on 09.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORMPOPULATION_H
#define PORR_SWARMS_GLOWWORMPOPULATION_H

#include <algorithm>
#include <numeric>

#include "Glowworm.h"

namespace gso {
    class GlowwormPopulation {
    private:
        std::vector<Glowworm> population;
        const Parameters parameters;

        void updateGlowwormLuciferine(Glowworm&);
        void moveGlowworm(Glowworm&);
    public:

    };
}

#endif //PORR_SWARMS_GLOWWORMPOPULATION_H
