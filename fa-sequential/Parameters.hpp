//
// Created by Komorowski on 16.12.2019.
//

#ifndef PORR_SWARMS_FIREFLYALGORITHM_PARAMETERS
#define PORR_SWARMS_FIREFLYALGORITHM_PARAMETERS


class Parameters {
public:
    const int numberOfFireflies;    //defines number of fireflies
    const int numberOfDimensions;   //describe space where algorithm works, for instance value 3 means 3D space
    const int dimensionRange;       //scope of values for all dimensions, for example if x is range, scope is from -x to x
    const float attractivenessFactor;//factor responsible for luring of fireflies, if higher, the fireflies make bigger moves in direction of the others
    const float absorptionFactor;   //factor stands for impact of distance between fireflies, if higher, the fireflies from far away lure much worse


    Parameters(const int numberOfFireflies, const int numberOfDimensions, const int dimensionRange,
               const int attractivenessFactor, const int absorptionFactor
    ) : numberOfFireflies(numberOfFireflies), numberOfDimensions(numberOfDimensions),  dimensionRange(dimensionRange),
        attractivenessFactor(attractivenessFactor), absorptionFactor(absorptionFactor) {}
};

#endif