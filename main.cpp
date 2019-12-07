#include <iostream>
#include "fa-sequential/FireflyAlgorithm.h"

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;

    //Firefly algorithm
    //Sequential run
    // attractivityFactor (recommended values: 0.5 - 4), absorptionFactor (recommended values: 1e-9 - 1e-3)
    FireflyAlgorithm algorithm =  FireflyAlgorithm(3,3, 40,1, 1e-3);
    algorithm.RunAlgorithm(20, true);

    return 0;
}