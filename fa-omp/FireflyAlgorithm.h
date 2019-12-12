//
// Created by Adrian on 07.12.2019.
//

#ifndef PORR_SWARMS_FIREFLYALGORITHM_H
#define PORR_SWARMS_FIREFLYALGORITHM_H

class FireflyAlgorithm
{
private:
    int numberOfFireflies;              //defines number of fireflies
    int numberOfDimensions;             //describe space where algorithm works, for instance value 3 means 3D space
    int dimensionRange;                 //scope of values for all dimensions, for example if x is range, scope is from -x to x
    float** firefliesTable;             //two dimension table which stores data about current position of each firefly
    float** firefliesTableTemporary;    //copy of previous table, used in order to keep local changes of iteration before update whole table at once
    float attractivityFactor;           //factor responsible for luring of fireflies, if higher, the fireflies make bigger moves in direction of the others
    float absorptionFactor;             //factor stands for impact of distance between fireflies, if higher, the fireflies from far away lure much worse
    bool debugMode;                     //flag for displaying extra info for debugging purposes

    void InitializeFirefliesTable(float** & firefliesTable, int numberOfFireflies, int numberOfDimensions);
    void GenerateRandomPositionsOfFireflies();
    void PrintCurrentPositionsOfFireflies();
    void SaveTemporaryFirefliesPosition();
    void CopyToTemporaryFirefliesPositionTable();
    float CountCostFunction(float* firefly);
    void CleanUpFireflyMoveVector(float* & fireflyMove);
    void CalculateFireflyMoveVector(float* & fireflyMoveVector, float* mainFirefly, float* secondFirefly);
    void UpdateFirefliesTemporaryTable(float* fireflyMoveVector, int fireflyNo);


public:
    FireflyAlgorithm(int numberOfFireflies, int numberOfDimensions, int dimensionRange, float attractivityFactor, float absorptionFactor);
    ~FireflyAlgorithm();
    void RunAlgorithm(int numberOfIterations, bool debugMode);


};


#endif //PORR_SWARMS_FIREFLYALGORITHM_H
