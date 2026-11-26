#include <cmath>
#include "blackScholes.h"
#include "delta.h"
#include "normalDistribution.h"

namespace blackscholes{
    double calculate_pricing_Call(const double S, const double K, const double r, const double sigma, const double T){
        if (T == 0.0) {
            if (K < S) {
                return (S - K);
            }
            else{
                return 0.0; 
            }
        }
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double d2 = d1 - sigma*sqrt(T);
        double Nd1 = normalDistribution::normalCDF(d1);
        double Nd2 = normalDistribution::normalCDF(d2);
        return S*Nd1 - K * exp(-r*T)*Nd2;
    }

    double calculate_pricing_Put(const double S, const double K, const double r, const double sigma, const double T){
        if (T == 0.0) {
            if (K > S){
                return (K - S);
            }
            else{
                return 0.0; 
            }
        }
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        double d2 = d1 - sigma*sqrt(T);
        double Nd1 = normalDistribution::normalCDF(-d1);
        double Nd2 = normalDistribution::normalCDF(-d2);
        return K * exp(-r*T)*Nd2 - S*Nd1;
    }
}