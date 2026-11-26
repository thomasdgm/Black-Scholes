#include <iostream>
#include <cmath>
#include "delta.h"
#include "normalDistribution.h"
using namespace std;

namespace delta{
    double calculate_d1(const double S, const double K, const double r, const double sigma, const double T){
        if(S <= 0.0 || K <= 0.0 || sigma <= 0.0 || T <= 0.0){
            cout << "Error: One of the parameters (S, K, sigma, T) is less than or equal to 0." << endl;
            return std::nan("");
        }
        else{
            return (log(S/K)+(r+(pow(sigma,2))/2)*T)/(sigma*sqrt(T));}
    }

    double calculate_delta_call(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = calculate_d1(S, K, r, sigma, T);
        return normalDistribution::normalCDF(d1);
    }

    double calculate_delta_put(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = calculate_d1(S, K, r, sigma, T);
        return normalDistribution::normalCDF(d1) - 1.0;
    }
}

