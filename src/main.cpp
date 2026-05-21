#include <iostream>
using namespace std;
#include "normalDistribution.h"
#include "delta.h"
#include "gamma.h"
#include "vega.h"
#include "theta.h"
#include "rho.h"

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
    cout << "Delta Call : " << d << endl;
    double g = gammas::calculate_gamma(S, K, r, sigma, T);
    cout << "Gamma : " << g << endl;
    double v = vega::calculate_vega(S, K, r, sigma, T);
    cout << "Vega : " << v << "%" << endl;
    double t = theta::calculate_theta_call(S, K, r, sigma, T);
    cout << "Theta Call : " << t << endl;
    double rho = rho::calculate_rho_call(S, K, r, sigma, T);
    cout << "Rho Call : " << rho << "%" << endl;
    return 0;
}