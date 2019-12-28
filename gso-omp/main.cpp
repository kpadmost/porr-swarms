//
// Created by Konstantin on 08.12.2019.
//
#include <iostream>
#include <numeric>

#include <ctime>
#include <algorithm>

#include "GlowwormSwarm.h"

using namespace std;

float zad1(const gso::Position& pos, const float _) {
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

float zad2(const gso::Position& pos, const float p) {
    float alpha = 0.0f, beta = 0.0f, penalty = 0.0f;
    const size_t size = pos.size();
    for(int i = 0; i < size - 1; i++) {
        alpha += std::pow(pos[i + 1] - std::pow(pos[i], 2), 2);
        beta += std::pow(1.0f - pos[i], 2);
        penalty += std::pow(pos[i] - i - 1.0f, 2);
    }
    //std::cout << "a " << alpha << " b "<< beta  << " p " << penalty << std::endl;
    return 100 * alpha + beta + p * std::pow(std::fmax(0.0f, penalty - size * 10), 2);
}

void test(const unsigned int dim, const int iternum, const int population, const float r0, const int num_threads, const int simulation_number, gso::CostFunction funck) {
    // set env
    std::vector<float> times(simulation_number, 0);
    std::vector<float> best_results(simulation_number, 0.0f);
    omp_set_num_threads(num_threads);
    std::cout << "endsim";
    for(int i = 0; i < simulation_number; i++) {
        gso::GlowwormSwarm swarm(funck, dim * r0, population, dim);
        const clock_t begin_time = clock();
        swarm.runAlgorithm(iternum);
        const float res =  float( clock () - begin_time ) /  CLOCKS_PER_SEC;
        times[i] = res;
        best_results[i] = funck(swarm.getBestWorm(), 0.0f);
        std::cout << " " << i;
    }
   /* std::cout << std::endl;
    for(int i = 0; i < simulation_number; i++) {
        std::cout << best_results[i] << ", " << times[i] << std::endl;
    }*/

    // sort results
    /*std::sort(best_results.begin(), best_results.end());
    std::cout << "f " << best_results[0] << ", "
               << best_results[simulation_number / 2] << ", " << best_results[simulation_number - 1] << std::endl;
    std::sort(times.begin(), times.end());
    std::cout << "t " << times[0] << ", "
              << times[simulation_number / 2] << ", " << times[simulation_number - 1] << std::endl;*/

}

void allTests() {
    // 10 simulations

    constexpr int dim = 3;
    constexpr int iternum = 1000;
    constexpr float r1 = 20.0f;
    const int population = 10;
    std::cout << "10 simulations of zad1 " << std::endl;

    std::vector<int> thrnum({2, 3, 4, 5, 6, 7, 8, 16, 32});
    for(auto val :thrnum) {
        std::cout << "thrnum " << val << std::endl;
        test(dim, iternum, population, r1, val, 10, zad1);
    }
    std::cout << std::endl << "10 simulations of zad2 " << std::endl;
    for(auto val :thrnum) {
        std::cout << "thrnum " << val << std::endl;
        test(dim, iternum, population, r1,  val, 10, zad2);
    }
}

int main() {
    constexpr int dim = 10;
    constexpr int iternum = 100;
    constexpr float r1 = 40.0f;
    omp_set_dynamic(0);
//    allTests();
    omp_set_num_threads(8);

    gso::GlowwormSwarm swarm(zad1, dim * r1, 8 * 7, dim);
    const clock_t begin_time = clock();
    swarm.runAlgorithm(iternum);
    std::cout << "Task no. 1 execution time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    gso::Position best = swarm.getBestWorm();
    //std::cout << endl << "res " << zad1(best, 1 + 100 * iternum);
    //std::cout << endl << "res " << zad1(best, 0);




    gso::GlowwormSwarm swarm2(zad2, dim * r1, 8 * 7, dim);
    const clock_t begin_time2 = clock();
    swarm.runAlgorithm(iternum);
    std::cout << "Task no. 2 execution time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    gso::Position best2 = swarm.getBestWorm();
    //std::cout << endl << "res " << zad2(best, 1 + 100 * iternum);
    //std::cout << endl << "res " << zad2(best, 0);
    return 0;
}