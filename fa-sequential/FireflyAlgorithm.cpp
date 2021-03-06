//
// Created by Adrian on 07.12.2019.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <omp.h>
#include "FireflyAlgorithm.h"

#ifndef  __MINGW32__
#define M_E	2.71828182845904523536
#endif

using namespace std;

FireflyAlgorithm::FireflyAlgorithm(const int numberOfFireflies, const int numberOfDimensions, const int dimensionRange,
                                   const float attractivenessFactor, const float absorptionFactor)
        : parameters(numberOfFireflies, numberOfDimensions, dimensionRange, attractivenessFactor, absorptionFactor) {
    this->debugMode;
    this->costFunctionFlag;

    InitializeFirefliesTable(this->firefliesTable, numberOfFireflies, numberOfDimensions);
    InitializeFirefliesTable(this->firefliesTableTemporary, numberOfFireflies, dimensionRange);
    GenerateRandomPositionsOfFireflies();
    CopyToTemporaryFirefliesPositionTable();
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
            this->firefliesTable[i][j] = random.getFromRange(-40.0, 40.0); //((float)rand() / RAND_MAX) * 2.0f * this->parameters.dimensionRange - 40.0f;
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
        sigma2 += pow((firefly[i] - i - 1), 2);
    }

    if(sigma2 > this->parameters.numberOfDimensions * 10) {
        sigma += *d * pow(sigma2 - (10 * this->parameters.numberOfDimensions), 2);
    }

    for(int i = 0; i < this->parameters.numberOfDimensions - 1; i++){
        float a = pow((firefly[i+1] - pow(firefly[i], 2)), 2);
        float b = pow((1.0f - firefly[i]), 2);
        //cout << "a " << a << " b " << b << endl;
        sigma += ((100 * a) + b);
    }
    // cout << "sig " << sigma << endl;
    return sigma;
}

void FireflyAlgorithm::RunAlgorithm(int numberOfIterations, bool _debugMode, bool _costFunctionFlag) {
    this->debugMode = _debugMode;
    this->costFunctionFlag = _costFunctionFlag;
    float d = 10.0f; // parameter for cost function 2
    srand(time(NULL));

    //Checking cost function values before algorithm's run
    if(this->debugMode) {
        std::cout << "Cost function values at the beginning of algorithm"<< std::endl;
        for (int i = 0; i < parameters.numberOfFireflies; i++) {
            std::cout << CountCostFunction(firefliesTable[i]) << " " << std::endl;
            std::cout << CountCostFunction2(firefliesTable[i], &d) << " " << std::endl;
        }
        cout << endl;
    }



    //float *fireflyMoveVector = new float[this->dimensionRange];
    for (int iterationNo = 0; iterationNo < numberOfIterations; iterationNo++) {
        if(this->debugMode)
            std::cout << "Iteration no. " << iterationNo << std::endl;

        for (int i = 0; i < parameters.numberOfFireflies; i++) { // P
            float *fireflyMoveVector = new float[this->parameters.numberOfDimensions];
            for(int j = 0; j < parameters.numberOfDimensions; j++)
                fireflyMoveVector[j] = this->firefliesTable[i][j];

            //CleanUpFireflyMoveVector(fireflyMoveVector);
            for (int j = 0; j < parameters.numberOfFireflies; j++) {
                if(this->costFunctionFlag)
                {
                    if (CountCostFunction2(fireflyMoveVector, &d) > CountCostFunction2(this->firefliesTable[j], &d))
                        CalculateFireflyMoveVector(fireflyMoveVector, this->firefliesTable[i], this->firefliesTable[j]);
                    d += 100;
                } else {
                    if (CountCostFunction(fireflyMoveVector) > CountCostFunction(this->firefliesTable[j]))
                        CalculateFireflyMoveVector(fireflyMoveVector, this->firefliesTable[i], this->firefliesTable[j]);
                }
            }

            UpdateFirefliesTemporaryTable(fireflyMoveVector, i);
            delete fireflyMoveVector;


        }
        SaveTemporaryFirefliesPosition();
    }

    //Checking cost function values after algorithm's run
    if(this->debugMode) {
        std::cout << "Cost function values at the end of algorithm"<< std::endl;
        for (int i = 0; i < parameters.numberOfFireflies; i++) {
            std::cout << CountCostFunction(firefliesTable[i]) << " " << std::endl;
            std::cout << CountCostFunction2(firefliesTable[i], &d) << " " << std::endl;
        }
        cout << endl;
    }
    //delete fireflyMoveVector;
}

void FireflyAlgorithm::CleanUpFireflyMoveVector(float* & fireflyMoveVector){
    for(int i = 0; i < this->parameters.numberOfDimensions; i++)
        fireflyMoveVector[i] = 0.0f;
}

void FireflyAlgorithm::CalculateFireflyMoveVector(float* fireflyMoveVector, float* mainFirefly, float* secondFirefly){
    // calc beta
    // calc rij
    // calc ui
    //calc distance
    float dist = 0.0f;
    for(int dim = 0; dim < parameters.numberOfDimensions; dim++) {
        dist += pow(fireflyMoveVector[dim] - secondFirefly[dim], 2);
    }

    for (int dimension = 0; dimension < this->parameters.numberOfDimensions; dimension++) {
        float randomValue = random.getFromRange(-1.0, 1.0); //((float)(2*rand() - (RAND_MAX)) /  RAND_MAX);
        fireflyMoveVector[dimension] = fireflyMoveVector[dimension]+ randomValue +  this->parameters.attractivenessFactor *
                                                                                    pow(M_E, -(this->parameters.absorptionFactor*dist)) * (secondFirefly[dimension] - fireflyMoveVector[dimension]);
    }
}

void FireflyAlgorithm::UpdateFirefliesTemporaryTable(float* fireflyMoveVector, int fireflyNo){
    float previewValue = 0.0f;
    for (int dimension = 0; dimension < this->parameters.numberOfDimensions; dimension++) {
        if(this->debugMode)
            std::cout << "Firefly no. " << fireflyNo << " moves in dimension no. " << dimension << " from " <<  firefliesTableTemporary[fireflyNo][dimension] << " to ";

        // previewValue = firefliesTableTemporary[fireflyNo][dimension] + fireflyMoveVector[dimension];
        previewValue = fireflyMoveVector[dimension];
        if(this->costFunctionFlag)
        {
            if(previewValue > 40.0f)
                firefliesTableTemporary[fireflyNo][dimension] = 40.0f;
            else if(previewValue < -40.0f)
                firefliesTableTemporary[fireflyNo][dimension] = -40.0f;
            else
                firefliesTableTemporary[fireflyNo][dimension] = previewValue;
        } else {
            if(previewValue > 40.0f)
                firefliesTableTemporary[fireflyNo][dimension] = 40.0f - (previewValue - 40.0f);
            else if(previewValue < -40.0f)
                firefliesTableTemporary[fireflyNo][dimension] = -40.0f - (previewValue + 40.0f);
            else
                firefliesTableTemporary[fireflyNo][dimension] = previewValue;
        }

        if(this->debugMode)
            std::cout << firefliesTableTemporary[fireflyNo][dimension] << std::endl;
    }
}

void FireflyAlgorithm::printCost() {
    cout << "cost";
    for(int i = 0; i < parameters.numberOfFireflies; i++) {
        std::cout << CountCostFunction(firefliesTable[i]) << " ";
    }
    cout << endl;
}
