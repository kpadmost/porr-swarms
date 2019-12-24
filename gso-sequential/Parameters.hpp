#ifndef PORR_PARAMETERS
#define PORR_PARAMETERS

#include <functional>
#include <vector>

namespace gso {

    typedef std::vector<float> Position;
    class Parameters { // algorithm parameters
     public:
        const float rs;
        const size_t populationNumber;
        const unsigned int dimensions;
        // empirically best from the book
        const int nt = 5;
        const float l0 = 5.0f;
        const float s = 0.03f;
        const float ro = 0.4f;
        const float gamma = 0.6f;
        const float beta = 0.08f;

        const std::function<float(const Position &)> costFunction;

        Parameters(const std::function<float(const Position &)> &consFunction, float rs,
                   const size_t populationNumber, unsigned int dimensions,
                   const float ro, const float gamma, const float beta, const float s, const int neighbours,
                   const float l0
        ) : ro(ro), gamma(gamma), beta(beta), nt(neighbours), l0(l0), costFunction(consFunction), s(s),
            rs(rs), populationNumber(populationNumber), dimensions(dimensions) {}

        Parameters(
                const std::function<float(const Position &)> &consFunction, float rs,
                size_t populationNumber, unsigned int dimensions
        ) // parameters from paper
                : costFunction(consFunction), rs(rs), populationNumber(populationNumber), dimensions(dimensions) {}
    };
}
#endif