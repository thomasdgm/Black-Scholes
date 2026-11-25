#ifndef _BLACKSCHOLES_H
#define _BLACKSCHOLES_H

namespace blackscholes{
    double calculate_pricing_Call(const double S, const double K, const double r, const double sigma, const double T);
    double calculate_pricing_Put(const double S, const double K, const double r, const double sigma, const double T);

}

#endif