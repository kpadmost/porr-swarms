#ifndef PORR_PARAMETERS
#define PORR_PARAMETERS

#include <functional>
#include <vector>

typedef std::vector<float> Position;

class Parameters { // algorithm parameters
private:
    unsigned int t; // time
public:
    unsigned int getT() const {
        return t;
    }

    inline void updateT() { t++; }

public:
    const float ro;
    const float gamma;
    const float beta;
    const int neighbours;
    const int l0;
    const float s;

    const std::function<float(const Position&)> consFunction;

    Parameters(const float ro, const float gamma, const float beta, const int neighbours, const int l0,
               const std::function<float(const Position&)> &consFunction) : ro(ro), gamma(gamma), beta(beta),
                                                                            neighbours(neighbours), l0(l0),
                                                                            consFunction(consFunction), t(0), s(0) {}

    Parameters(const std::function<float(const Position &)> &consFunction) : consFunction(consFunction), ro(0.4f), // parameters from paper
                                                                                gamma(0.6f), beta(0.08f), neighbours(5),
                                                                                s(0.03), l0(5), t(0) {}
};

#endif