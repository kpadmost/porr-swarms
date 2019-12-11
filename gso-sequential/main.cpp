//
// Created by Konstantin on 08.12.2019.
//
#include <iostream>
#include <numeric>
#include "GlowwormSwarm.h"
using namespace std;

float zad1(const Position& pos) {
    const float a1 = accumulate(pos.begin(), pos.end(), 0.0f, [] (const float i, const float &xi) { return i + xi * xi;});

    size_t i = 1;
    auto cosmult = [&i] (float init, float a) {
        const float res = cos(a / i);
        i++;
        return init * res;
    };
    const float a2 = accumulate(pos.begin(), pos.end(), 1.0f, cosmult);
    return (1 / 40.0f) * a1 + 1 - a2;
}

int main() {
    gso::GlowwormSwarm swarm(zad1, 500, 7.0f, 90, 2);
    swarm.runAlgorithm();
    Position best = swarm.getBestWorm();
    return 0;
}