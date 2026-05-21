#include <iostream>
using namespace std;
#include <cmath>
#include "theta.h"
#include "delta.h"
#include "normalDistribution.h"

namespace theta{
    double calculate_theta_call(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double n = normalDistribution::densite(d1);
        double d2 = d1 - sigma*sqrt(T);
        double N = normalDistribution::normalCDF(d2);
        return (-((S*n*sigma)/2.0*sqrt(T))-r*K*exp(-r*T)*N)/365.0;
    }

    double calculate_theta_put(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double n = normalDistribution::densite(d1);
        double d2 = d1 - sigma*sqrt(T);
        double N = normalDistribution::normalCDF(-d2);
        return (-((S*n*sigma)/2.0*sqrt(T))+r*K*exp(-r*T)*N)/365.0;
    }

}