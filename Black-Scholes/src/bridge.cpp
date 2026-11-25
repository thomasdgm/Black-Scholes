#include "blackScholes.h"
#include "delta.h"
#include "gamma.h"
#include "vega.h"
#include "theta.h"
#include "rho.h"
#include "volatility.h"

extern "C" {
    double py_call_price(double S, double K, double r, double sigma, double T) {
        return blackscholes::calculate_pricing_Call(S, K, r, sigma, T);
    }

    double py_put_price(double S, double K, double r, double sigma, double T) {
        return blackscholes::calculate_pricing_Put(S, K, r, sigma, T);
    }

    // Grecs
    double py_delta_call(double S, double K, double r, double sigma, double T) {
        return delta::calculate_delta_call(S, K, r, sigma, T);
    }

    double py_delta_put(double S, double K, double r, double sigma, double T) {
        return delta::calculate_delta_put(S, K, r, sigma, T);
    }

    double py_gamma(double S, double K, double r, double sigma, double T) {
        return gammas::calculate_gamma(S, K, r, sigma, T);
    }

    double py_vega(double S, double K, double r, double sigma, double T) {
        return vega::calculate_vega(S, K, r, sigma, T);
    }

    double py_theta_call(double S, double K, double r, double sigma, double T) {
        return theta::calculate_theta_call(S, K, r, sigma, T);
    }

    double py_theta_put(double S, double K, double r, double sigma, double T) {
        return theta::calculate_theta_put(S, K, r, sigma, T);
    }

    double py_rho_call(double S, double K, double r, double sigma, double T) {
        return rho::calculate_rho_call(S, K, r, sigma, T);
    }
    
    double py_rho_put(double S, double K, double r, double sigma, double T) {
        return rho::calculate_rho_put(S, K, r, sigma, T);
    }
}