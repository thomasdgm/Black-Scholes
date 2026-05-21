#ifndef _DELTA_H
#define _DELTA_H

namespace delta{
    double calculate_d1(const double S, const double K, const double r, const double sigma, const double T);

    double calculate_delta_call(const double S, const double K, const double r, const double sigma, const double T);

    double calculate_delta_put(const double S, const double K, const double r, const double sigma, const double T);
}



#endif