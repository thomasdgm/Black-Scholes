#include <iostream>
#include <cmath>
#include "normalDistribution.h"
#include "delta.h"
#include "gamma.h"
#include "vega.h"
#include "theta.h"
#include "rho.h"
#include "blackScholes.h"
#include "volatility.h"
using namespace std;

int main(){
    double S = 100.0;    // Underlying price
    double K = 100.0;    // Strike
    double r = 0.05;     // Interest rate (5%)
    double sigma = 0.2;  // Volatility (20%)
    double T = 1.0; // Remaining time
    double d = delta::calculate_delta_call(S, K, r, sigma, T);
    cout << "(Delta) If the stock goes up by €1, I win : " << d << endl;
    double g = gammas::calculate_gamma(S, K, r, sigma, T);
    cout << "(Gamma) If the stock increases by €1, then the delta rises by : " << g << endl;
    double v = vega::calculate_vega(S, K, r, sigma, T);
    cout << "(Vega) If the volatility increases by 1%, the option price varies from : " << v << "€" << endl;
    double t = theta::calculate_theta_call(S, K, r, sigma, T);
    cout << "(Theta Call) The option loses : " << t << " every day" << endl;
    double rho = rho::calculate_rho_call(S, K, r, sigma, T);
    cout << "(Rho Call) If the interest rate increases by 1%, the option price varies by : " << rho << "€" << endl;
    double bC = blackscholes::calculate_pricing_Call(S, K, r, sigma, T);
    double bP = blackscholes::calculate_pricing_Put(S, K, r, sigma, T);
    cout << "The price of the Call option should theoretically be : " << bC << endl;
    cout << "The price of the Put option should theoretically be : " << bP << endl;
    double vo = volatility::implied_volatility_Put(S,K,r,T,5.5735);
    cout << vo << endl;
    return 0;
}