//
// Created by Adrian on 07.12.2019.
//

#ifndef PORR_SWARMS_FIREFLYALGORITHM_H
#define PORR_SWARMS_FIREFLYALGORITHM_H


#include "Parameters.hpp"

class FireflyAlgorithm
{
private:
    Parameters parameters;              // algorithm parameters
    float** firefliesTable;             //two dimension table which stores data about current position of each firefly
    float** firefliesTableTemporary;    //copy of previous table, used in order to keep local changes of iteration before update whole table at once

    bool debugMode;                     //flag for displaying extra info for debugging purposes
    bool costFunctionFlag;              //if false then CountCostFunction otherwise CountCostFunction2

    void printCost();
    void InitializeFirefliesTable(float** & firefliesTable, int numberOfFireflies, int numberOfDimensions);
    void GenerateRandomPositionsOfFireflies();
    void PrintCurrentPositionsOfFireflies();
    void SaveTemporaryFirefliesPosition();
    void CopyToTemporaryFirefliesPositionTable();
    float CountCostFunction(float* firefly);
    float CountCostFunction2(float* firefly, float* d);
    void CleanUpFireflyMoveVector(float* & fireflyMove);
    void CalculateFireflyMoveVector(float* fireflyMoveVector, float* mainFirefly, float* secondFirefly);
    void UpdateFirefliesTemporaryTable(float* fireflyMoveVector, int fireflyNo);


public:
    FireflyAlgorithm(const int numberOfFireflies, const int numberOfDimensions, const int dimensionRange,
                     const float attractivenessFactor, const float absorptionFactor);
    ~FireflyAlgorithm();
    void RunAlgorithm(int numberOfIterations, bool debugMode, bool costFunctionFlag);


};


#endif //PORR_SWARMS_FIREFLYALGORITHM_H
