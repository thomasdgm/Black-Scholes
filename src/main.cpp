#include <iostream>
using namespace std;
#include "normalDistribution.h"
#include "delta.h"
#include "gamma.h"

int main(){
    normalDistribution::genererNombreDefaut();
    normalDistribution::genererNombre(30.0, 8.0);
    double n = normalDistribution::normalCDF(2);
    cout << n << endl;
    double S = 100.0;    // Prix du sous-jacent
    double K = 100.0;    // Strike
    double r = 0.05;     // Taux d'intérêt (5%)
    double sigma = 0.2;  // Volatilité (20%)
    double T = 1.0;
    double d = delta::calculate_delta_call(S, K, r, sigma, T);
    cout << d << endl;
    double g = gammas::calculate_gamma(S, K, r, sigma, T);
    cout << g << endl;
    return 0;
}