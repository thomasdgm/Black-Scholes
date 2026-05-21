#include <cmath>
#include "vega.h"
#include "delta.h"
#include "normalDistribution.h"

namespace vega{
    double calculate_vega(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double n = normalDistribution::densite(d1);
        return (S * sqrt(T) * n)/100.0;
    }
};