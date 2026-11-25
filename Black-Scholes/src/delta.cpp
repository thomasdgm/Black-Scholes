#include <iostream>
using namespace std;
#include <cmath>
#include "delta.h"
#include "normalDistribution.h"

namespace delta{
    double calculate_d1(const double S, const double K, const double r, const double sigma, const double T){
        if(sigma*sqrt(T)==0){
            cout << "Erreur on ne peut pas diviser par 0." << endl;
            return -1;
        }
        else{
            return (log(S/K)+(r+(pow(sigma,2))/2)*T)/(sigma*sqrt(T));}
    }

    double calculate_delta_call(const double S, const double K, const double r, const double sigma, const double T){
        if(T < 0.0){
            cout << "Erreur : Le temps est égal ou inferieur à zéro." << endl;
            return -1;
        }
        else{
            double d1 = calculate_d1(S, K, r, sigma, T);
            return normalDistribution::normalCDF(d1);
        }
    }

    double calculate_delta_put(const double S, const double K, const double r, const double sigma, const double T){
        if(T < 0.0){
            cout << "Erreur : Le temps est égal ou inferieur à zéro." << endl;
            return -1;
        }
        else{
            double d1 = calculate_d1(S, K, r, sigma, T);
            return normalDistribution::normalCDF(d1) - 1.0;
        }
    }
}

