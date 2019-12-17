//
// Created by Konstantin on 08.12.2019.
//
#include <iostream>
#include <numeric>

#include <ctime>

#include "GlowwormSwarm.h"

using namespace std;

float zad1(const gso::Position& pos, const double _) {
    float alpha = 0.0f, beta=1.0f;
    const int size = pos.size();
    int i;
    // #pragma omp parallel for private(i) shared(size, pos) reduction(+:alpha) reduction(*:beta)
    for(i = 0; i < size; i++) {
        const float xi = pos[i];
        alpha += xi * xi;
        beta *= cos(xi / (i + 1));
    }

    return (1 / 40.0f) * alpha + 1 - beta;
}

float zad2(const gso::Position& pos, const double p) {
    float alpha = 0.0f, beta = 0.0f, penalty = 0.0f;
    const size_t size = pos.size();
    for(int i = 0; i < size - 1; i++) {
        alpha += std::pow(pos[i + 1] - std::pow(pos[i], 2), 2);
        beta += std::pow(1.0f - pos[i], 2);
        penalty += std::pow(pos[i] - i - 1, 2);
    }

    return 100 * alpha + beta + p * std::pow(std::fmax(0.0f, penalty - size * 10), 2);
}

int main() {
    constexpr int dim = 10;
    constexpr int iternum = 1000;
    constexpr float r1 = 40.0f;
    omp_set_dynamic(0);
    omp_set_num_threads(8);

    gso::GlowwormSwarm swarm(zad2, dim * r1, 8 * 7, dim);
    const clock_t begin_time = clock();
    swarm.runAlgorithm(iternum);
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    gso::Position best = swarm.getBestWorm();
    std::cout << endl << "res " << zad2(best, 0);
    return 0;
}