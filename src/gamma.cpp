#include <iostream>
using namespace std;
#include <cmath>
#include "gamma.h"
#include "delta.h"
#include "normalDistribution.h"

namespace gammas{
    double calculate_gamma(const double S, const double K, const double r, const double sigma, const double T){
        double d1 = delta::calculate_d1(S, K, r, sigma, T);
        if((S*sigma*sqrt(T))==0){
            cout << "Erreur impossible de diviser par 0" << endl;
        }
        return normalDistribution::densite(d1)/(S*sigma*sqrt(T));
    }
}