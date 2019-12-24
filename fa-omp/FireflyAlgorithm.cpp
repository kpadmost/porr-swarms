//
// Created by Adrian on 07.12.2019.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include "FireflyAlgorithm.h"

using namespace std;

#ifndef  __MINGW32__
#define M_E	2.71828182845904523536
#endif

FireflyAlgorithm::FireflyAlgorithm(const int numberOfFireflies, const int numberOfDimensions, const int dimensionRange,
                                   const float attractivenessFactor, const float absorptionFactor)
        : parameters(numberOfFireflies, numberOfDimensions, dimensionRange, attractivenessFactor, absorptionFactor) {
    this->debugMode;

    InitializeFirefliesTable(this->firefliesTable, numberOfFireflies, numberOfDimensions);
    InitializeFirefliesTable(this->firefliesTableTemporary, numberOfFireflies, dimensionRange);
    GenerateRandomPositionsOfFireflies();
    CopyToTemporaryFirefliesPositionTable();
    //PrintCurrentPositionsOfFireflies();
}

FireflyAlgorithm::~FireflyAlgorithm(){
    for(int a = 0; a < this->parameters.numberOfFireflies; a++){
        delete this->firefliesTable[a];
        delete this->firefliesTableTemporary[a];
    }
    delete this->firefliesTable;
    delete this->firefliesTableTemporary;
}

void FireflyAlgorithm::InitializeFirefliesTable(float** & _firefliesTable, const int numberOfFireflies, const int numberOfDimensions) {
    _firefliesTable = new float*[numberOfFireflies];
    for(int i = 0; i < numberOfFireflies; i++)
        _firefliesTable[i] = new float[numberOfDimensions];
};


void FireflyAlgorithm::GenerateRandomPositionsOfFireflies() {
    for(int i = 0; i < this->parameters.numberOfFireflies; i++)  // P
        for(int j = 0; j < this->parameters.numberOfDimensions; j++){
            this->firefliesTable[i][j] = ((float)rand() / RAND_MAX) * 2.0f * this->parameters.dimensionRange - 40.0f;
        }

}

void FireflyAlgorithm::SaveTemporaryFirefliesPosition() {
    for(int i = 0; i < this->parameters.numberOfFireflies; i++)
        for(int j = 0; j < this->parameters.numberOfDimensions; j++){
            this->firefliesTable[i][j] = this->firefliesTableTemporary[i][j];
        }
}

void FireflyAlgorithm::CopyToTemporaryFirefliesPositionTable() {
    for(int i = 0; i < this->parameters.numberOfFireflies; i++)
        for(int j = 0; j < this->parameters.numberOfDimensions; j++){
            this->firefliesTableTemporary[i][j] = this->firefliesTable[i][j];
        }
}

void FireflyAlgorithm::PrintCurrentPositionsOfFireflies() {
    for(int i = 0; i < this->parameters.numberOfFireflies; i++)
        for(int j = 0; j < this->parameters.numberOfDimensions; j++)
            std::cout<<this->firefliesTable[i][j]<<std::endl;
}

float FireflyAlgorithm::CountCostFunction(float* firefly){
    float sigma = 0.0f, pi = 1.0f;

    for(int i = 0; i < this->parameters.numberOfDimensions; i++){
        sigma += pow(firefly[i],2);
        pi *= cos(firefly[i]/(i+1));

    }
    return sigma/40 + 1 - pi;
}

float FireflyAlgorithm::CountCostFunction2(float* firefly, float* d){
    float sigma = 0.0f, sigma2 = 0.0f;

    for(int i = 0; i < this->parameters.numberOfDimensions; i++){
        sigma2 += pow((firefly[i] - (i + 1)), 2);
    }

    if(sigma2 > this->parameters.numberOfDimensions * 10) {
        sigma += *d * pow(sigma2 - (10 * this->parameters.numberOfDimensions), 2);
    }

    for(int i = 0; i < this->parameters.numberOfDimensions - 1; i++){
        float a = pow((firefly[i+1] - pow(firefly[i], 2)), 2);
        float b = pow((1 - firefly[i]), 2);
        sigma += ((100 * a) + b);
    }
    return sigma;
}

void FireflyAlgorithm::RunAlgorithm(int numberOfIterations, bool _debugMode, bool _costFunctionFlag) {
    this->debugMode = _debugMode;
    this->costFunctionFlag = _costFunctionFlag;
    float d = 10.0f; // parameter for cost function 2

    srand(time(NULL));
    //float *fireflyMoveVector = new float[this->dimensionRange];
    for (int iterationNo = 0; iterationNo < numberOfIterations; iterationNo++) {
        if (this->debugMode)
            std::cout << "Iteration no. " << iterationNo << std::endl;


    # pragma omp parallel num_threads (8)
        {
    # pragma omp for lastprivate ( i )

        for (int i = 0; i < parameters.numberOfFireflies; i++) { // P
            float *fireflyMoveVector = new float[this->parameters.dimensionRange];
            //CleanUpFireflyMoveVector(fireflyMoveVector);
            for (int j = 0; j < parameters.numberOfFireflies; j++) {
                            if(this->costFunctionFlag)
                            {
                                if (CountCostFunction2(this->firefliesTable[i], &d) > CountCostFunction2(this->firefliesTable[j], &d))
                                                    CalculateFireflyMoveVector(fireflyMoveVector, this->firefliesTable[i], this->firefliesTable[j]);
                                 d *= 10;
                            } else {
                                if (CountCostFunction(this->firefliesTable[i]) > CountCostFunction(this->firefliesTable[j]))
                                                    CalculateFireflyMoveVector(fireflyMoveVector, this->firefliesTable[i], this->firefliesTable[j]);
                            }
                        }
            UpdateFirefliesTemporaryTable(fireflyMoveVector, i);
            delete fireflyMoveVector;
        }
    }
        SaveTemporaryFirefliesPosition();
    }

    //delete fireflyMoveVector;
}

void FireflyAlgorithm::CleanUpFireflyMoveVector(float* & fireflyMoveVector){
    for(int i = 0; i < this->parameters.numberOfDimensions; i++)
        fireflyMoveVector[i] = 0.0f;
}

void FireflyAlgorithm::CalculateFireflyMoveVector(float* & fireflyMoveVector, float* mainFirefly, float* secondFirefly){
    for (int dimension = 0; dimension < this->parameters.numberOfDimensions; dimension++) {
        float randomValue = ((float)(2*rand() - (RAND_MAX)) /  RAND_MAX);
        fireflyMoveVector[dimension] += randomValue + this->parameters.attractivenessFactor *
                                                      pow(M_E, -(this->parameters.absorptionFactor*pow(mainFirefly[dimension]-secondFirefly[dimension],2)));
    }
}

void FireflyAlgorithm::UpdateFirefliesTemporaryTable(float* fireflyMoveVector, int fireflyNo){
    float previewValue = 0.0f;
    for (int dimension = 0; dimension < this->parameters.numberOfDimensions; dimension++) {
        if(this->debugMode)
            std::cout << "Firefly no. " << fireflyNo << " moves in dimension no. " << dimension << " from " <<  firefliesTableTemporary[fireflyNo][dimension] << " to ";

        previewValue = firefliesTableTemporary[fireflyNo][dimension] + fireflyMoveVector[dimension];
        if(previewValue > 40.0f)
            firefliesTableTemporary[fireflyNo][dimension] = 40.0f - (previewValue - 40.0f);
        else if(previewValue < -40.0f)
            firefliesTableTemporary[fireflyNo][dimension] = -40.0f - (previewValue + 40.0f);
        else
            firefliesTableTemporary[fireflyNo][dimension] = previewValue;

        if(this->debugMode)
            std::cout << firefliesTableTemporary[fireflyNo][dimension] << std::endl;
    }
}
