#include <cmath>
#include "normalDistribution.h"
#include "delta.h"
#include "rho.h"

namespace rho{
    double calculate_rho_call(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double d2 = d1 - sigma*sqrt(T);
        double N = normalDistribution::normalCDF(d2);
        return (K*T*exp(-r*T)*N)/100;
    }

    double calculate_rho_put(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double d2 = d1 - sigma*sqrt(T);
        double N = normalDistribution::normalCDF(-d2);
        return (-K*T*exp(-r*T)*N)/100;
    }
}