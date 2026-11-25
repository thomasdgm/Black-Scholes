#ifndef _RHO_H
#define _RHO_H

namespace rho{
    double calculate_rho_call(const double S, const double K, const double r, const double sigma, const double T);

    double calculate_rho_put(const double S, const double K, const double r, const double sigma, const double T);
}


#endif