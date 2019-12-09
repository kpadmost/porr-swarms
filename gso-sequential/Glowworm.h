//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORM_H
#define PORR_SWARMS_GLOWWORM_H

#include <memory>
#include <vector>
#include "Parameters.hpp"

namespace gso {
    class Glowworm {
    private:
        // global algorithm parameters, mostly constants thoughout algorithm
        std::shared_ptr<Parameters> pParameters;
        // specific per glowworm
        Position position;
        float neighbourhoodRange;
        float luciferin;
    public:
        void updateLuciferin();
    };

}

#endif //PORR_SWARMS_GLOWWORM_H
