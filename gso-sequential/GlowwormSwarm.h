//
// Created by Konstantin on 08.12.2019.
//

#ifndef PORR_SWARMS_GLOWWORMSWARM_H
#define PORR_SWARMS_GLOWWORMSWARM_H

namespace gso {
    class GlowwormSwarm {
    private:
        // main steps
        void movement(); // move glowworms
        void updateLuciferine(); // update luciferine
        void neighbourhoodRangeUpdate();

    public:
        void runAlgorithm();

        GlowwormSwarm();
    };
}

#endif //PORR_SWARMS_GLOWWORMSWARM_H
