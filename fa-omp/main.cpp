#include <iostream>
#include <ctime>
#include "FireflyAlgorithm.h"

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;

    //Firefly algorithm
    //Paraller run (OMP)
    // attractivityFactor (recommended values: 0.5 - 4), absorptionFactor (recommended values: 1e-9 - 1e-3)
    const clock_t begin_time = clock();
// do something

    FireflyAlgorithm algorithm =  FireflyAlgorithm(3,3, 40,1, 1e-3);
    algorithm.RunAlgorithm(20, true);
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;

    return 0;
}