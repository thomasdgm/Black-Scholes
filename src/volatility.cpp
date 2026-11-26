#include <iostream>
#include <cmath>
#include "volatility.h"
#include "blackScholes.h"
#include "vega.h"
using namespace std;

namespace volatility{
    double implied_volatility_Call(const double S, const double K, const double r, const double T, const double market_price){
        if (S <= 0.0 || K <= 0.0 || T <= 0.0 || market_price <= 0.0) {
            return std::nan("");
        }
        
        double sigma = 0.2;
        const double tol = 1e-6;

        for (int cmp = 0; cmp < 100; ++cmp) {
            double BS = blackscholes::calculate_pricing_Call(S, K, r, sigma, T);
            double f = BS - market_price;

            if (std::abs(f) <= tol) {
                return sigma;
            }

            double v = vega::calculate_vega(S, K, r, sigma, T) * 100.0;
            if (v < 1e-6) {
                v = 1e-6;
            }

            sigma = sigma - (f / v);

            if (sigma < 1e-4) sigma = 1e-4;
            if (sigma > 5.0)  sigma = 5.0;
        }

        cout << "Il y a une non convergence de sigma (Call)." << endl;
        return std::nan("");
    }

    double implied_volatility_Put(const double S, const double K, const double r, const double T, const double market_price){
        if (S <= 0.0 || K <= 0.0 || T <= 0.0 || market_price <= 0.0) {
            return std::nan("");
        }
        double sigma = 0.2;
        const double tol = 1e-6;

        for (int cmp = 0; cmp < 100; ++cmp) {
            double BS = blackscholes::calculate_pricing_Put(S, K, r, sigma, T);
            double f = BS - market_price;

            if (std::abs(f) <= tol) {
                return sigma;
            }

            double v = vega::calculate_vega(S, K, r, sigma, T) * 100.0;
            if (v < 1e-6) {
                v = 1e-6;
            }

            sigma = sigma - (f / v);

            if (sigma < 1e-4) sigma = 1e-4;
            if (sigma > 5.0)  sigma = 5.0;
        }

        cout << "Il y a une non convergence de sigma (Put)." << endl;
        return std::nan("");
    }
}