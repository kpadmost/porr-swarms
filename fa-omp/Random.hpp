//
// Created by Konstantin on 10.12.2019.
//

#ifndef PORR_SWARMS_RANDOM_HPP
#define PORR_SWARMS_RANDOM_HPP

#include <random>

namespace gso {
    template<typename T>
    class Random {
    private:
        std::mt19937 gen;
    public:
        Random() { std::random_device rd; gen = std::mt19937(rd());}
        inline T getFromRange(T l, T h) {
            std::uniform_real_distribution<T> dis(l, h);
            return dis(gen);
        }

    };
}

#endif //PORR_SWARMS_RANDOM_HPP
