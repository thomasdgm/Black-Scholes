#include <iostream>
using namespace std;
#include <cmath>
#include "normalDistribution.h"
#include "delta.h"
#include "gamma.h"
#include "vega.h"
#include "theta.h"
#include "rho.h"
#include "blackScholes.h"

int main(){
    double S = 100.0;    // Prix du sous-jacent
    double K = 100.0;    // Strike
    double r = 0.05;     // Taux d'intérêt (5%)
    double sigma = 0.2;  // Volatilité (20%)
    double T = 1.0; // Temps restant
    double d = delta::calculate_delta_call(S, K, r, sigma, T);
    cout << "(Delta) Si l'action monte de 1€, je gagne : " << d << endl;
    double g = gammas::calculate_gamma(S, K, r, sigma, T);
    cout << "(Gamma) Si l'action augmente de 1€ alors delta monte de : " << g << endl;
    double v = vega::calculate_vega(S, K, r, sigma, T);
    cout << "(Vega) Si la volatilité augmente de 1%, le prix de l'option varie de : " << v << "%" << endl;
    double t = theta::calculate_theta_call(S, K, r, sigma, T);
    cout << "(Theta Call) L'option perd : " << t << " chaque jour" << endl;
    double rho = rho::calculate_rho_call(S, K, r, sigma, T);
    cout << "(Rho Call) Si le taux d'intérêt augmente de 1%, le prix de l'option varie de : " << rho << "%" << endl;
    double bC = blackscholes::calculate_pricing_Call(S, K, r, sigma, T);
    double bP = blackscholes::calculate_pricing_Put(S, K, r, sigma, T);
    cout << "Le prix de l'option Call devrait théoriquement être de : " << bC << endl;
    cout << "Le prix de l'option Put devrait théoriquement être de : " << bP << endl;
    return 0;
}