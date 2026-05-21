#ifndef _DELTA_H
#define _DELTA_H

namespace delta{
    double calculate_d1(const double spot, const double strike, const double interest_rate, const double volatility, const double time);

    double calculate_delta_call(const double spot, const double strike, const double interest_rate, const double volatility, const double time);

    double calculate_delta_put(const double spot, const double strike, const double interest_rate, const double volatility, const double time);
}



#endif