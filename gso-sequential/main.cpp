//
// Created by Konstantin on 08.12.2019.
//
#include <iostream>
#include <numeric>
#include "GlowwormSwarm.h"
using namespace std;

inline float zad1(const gso::Position& pos) {
    float alpha = 0.0f, beta=1.0f;
    for(int i = 0; i < pos.size(); i++) {
        const float xi = pos[i];
        alpha += xi * xi;
        beta *= cos(xi / (i + 1));
    }
    return (1 / 40.0f) * alpha + 1 - beta;
}

int main() {
    gso::GlowwormSwarm swarm(zad1, 150, 100.0f, 200, 8);
    swarm.runAlgorithm();
    gso::Position best = swarm.getBestWorm();
    return 0;
}