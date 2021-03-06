#include <iostream>
#include <ctime>
#include <omp.h>
#include "FireflyAlgorithm.h"

#define NUMBER_OF_ITERATIONS 10000

using namespace std;

int main() {


    omp_set_dynamic(0);
    omp_set_num_threads(1);

    const clock_t begin_time = clock();

    //define parameters
    const int numberOfFireflies = 12;//5;
    const int numberOfDimensions = 20;//3;
    const int dimensionRange = 40;
    const float attractivenessFactor = 1.0f; // attractivityFactor (recommended values: 0.5 - 4)
    const float absorptionFactor = 1e-5; // absorptionFactor (recommended values: 1e-9 - 1e-3)

    FireflyAlgorithm algorithm =  FireflyAlgorithm(numberOfFireflies,numberOfDimensions,
                                                   dimensionRange, attractivenessFactor, absorptionFactor);

    //run task no. 1
    algorithm.RunAlgorithm(NUMBER_OF_ITERATIONS, false, false);

    std::cout << "Task no. 1 execution time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;

    const clock_t begin_time2 = clock();

    //run task no. 2
    algorithm.RunAlgorithm(NUMBER_OF_ITERATIONS, false, true);
    std::cout << "Task no. 2 execution time: " << float( clock () - begin_time2 ) /  CLOCKS_PER_SEC << std::endl;


    return 0;
}