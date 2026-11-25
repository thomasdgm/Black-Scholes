#ifndef _NEWTON_RAPHSON_H
#define _NEWTON_RAPHSON_H

namespace volatility{
    double implied_volatility_Call(const double S, const double K, const double r, const double T, const double market_price);

    double implied_volatility_Put(const double S, const double K, const double r, const double T, const double market_price);
}


#endif