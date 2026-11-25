#ifndef _THETA_H
#define _THETA_H

namespace theta{
    double calculate_theta_call(const double S, const double K, const double r, const double sigma, const double T);

    double calculate_theta_put(const double S, const double K, const double r, const double sigma, const double T);
}

#endif