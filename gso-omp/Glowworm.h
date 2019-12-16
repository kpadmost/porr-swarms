//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORM_H
#define PORR_SWARMS_GLOWWORM_H

#include <memory>
#include <vector>
#include "Parameters.hpp"
#include "Random.hpp"


namespace gso {
    class GlowwormSwarm;
    class Glowworm {
        friend class GlowwormSwarm;
    private:
        Position position;
        float neighbourhoodRange;
        float luciferin;
        float distance(const Glowworm&) const;
        void moveTowardsWorm(const Glowworm&, float step);

        void initializePosition(const size_t m, Random<float>&);
    public:
        Glowworm(const size_t m, const float l0, const float rs, Random<float>& random) : luciferin(l0), neighbourhoodRange(rs) {
            initializePosition(m, random);
        }
    };

}

#endif //PORR_SWARMS_GLOWWORM_H
