#include <iostream>
#include <ctime>
#include "FireflyAlgorithm.h"

#define NUMBER_OF_ITERATIONS 1000

using namespace std;

int main() {

    const clock_t begin_time = clock();

    //define parameters
    const int numberOfFireflies = 5;
    const int numberOfDimensions = 3;
    const int dimensionRange = 40;
    const float attractivenessFactor = 1.0f; // attractivityFactor (recommended values: 0.5 - 4)
    const float absorptionFactor = 1e-5; // absorptionFactor (recommended values: 1e-9 - 1e-3)

    FireflyAlgorithm algorithm =  FireflyAlgorithm(numberOfFireflies,numberOfDimensions,
                                                   dimensionRange, attractivenessFactor, absorptionFactor);
    algorithm.RunAlgorithm(NUMBER_OF_ITERATIONS, false, true);

    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;

    return 0;
}