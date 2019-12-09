//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORM_H
#define PORR_SWARMS_GLOWWORM_H

#include <memory>
#include <vector>
#include "Parameters.hpp"


namespace gso {
    class GlowwormPopulation;
    class Glowworm {
        friend class GlowwormPopulation;
    private:
        // global algorithm parameters, mostly constants thoughout algorithm

        // specific per glowworm
        Position position;
        float neighbourhoodRange;
        float luciferin;


        float distance(const Glowworm&) const;
    public:
        void updateLuciferin();
        void move(const std::vector<const Glowworm>& population); // WARNING! even though we are passing the one
    };

}

#endif //PORR_SWARMS_GLOWWORM_H
