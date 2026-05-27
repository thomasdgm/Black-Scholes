#include <iostream>
using namespace std;
#include <cmath>
#include "volatility.h"
#include "blackScholes.h"
#include "vega.h"

namespace volatility{
    double implied_volatility_Call(const double S, const double K, const double r, const double T, const double market_price){
        double sigma = 0.1;
        double BS = blackscholes::calculate_pricing_Call(S,K,r,sigma,T);
        double f = 1;
        double v = 1;
        int cmp = 0;
        while(f > pow(10.0,-6.0)){
            cout << "cmp " << cmp << endl;
            cmp ++;
            if(cmp >= 100){
                cout << "Il y a une non convergence de sigma.";
                return -1;
            }else if(v < 0.0001){
                cout << "Le vega est inférieur à 0,0001, la solution n'est donc pas fiable.";
                v = 0,0001;
            }else if(sigma < 0){
                cout << "Sigma est inférieur à zéro.";
                sigma = 0,0001;
            }else if(sigma > 5){
                cout << "Sigma est supérieur à 5 il y a divergence.";
                sigma = 5;
            }else if(BS == market_price){
                return sigma;
            }else{
                BS = blackscholes::calculate_pricing_Call(S,K,r,sigma,T);
                f = BS - market_price;
                v = vega::calculate_vega(S,K,r,sigma,T)*100;
                sigma = sigma - (f/v);
            }
            cout << "BS : " << BS << " f: " << f << " v : " << v << " sigma : " << sigma << endl;
        }
        return sigma;
    }

    double implied_volatility_Put(const double S, const double K, const double r, const double T, const double market_price){
        double sigma = 0.1;
        double BS = blackscholes::calculate_pricing_Put(S,K,r,sigma,T);
        double f = 1;
        double v = 1;
        int cmp = 0;
        while(f > pow(10.0,-6.0)){
            cout << "cmp " << cmp << endl;
            cmp ++;
            if(cmp >= 100){
                cout << "Il y a une non convergence de sigma.";
                return -1;
            }else if(v < 0.0001){
                cout << "Le vega est inférieur à 0,0001, la solution n'est donc pas fiable.";
                v = 0,0001;
            }else if(sigma < 0){
                cout << "Sigma est inférieur à zéro.";
                sigma = 0,0001;
            }else if(sigma > 5){
                cout << "Sigma est supérieur à 5 il y a divergence.";
                sigma = 5;
            }else if(BS == market_price){
                return sigma;
            }else{
                BS = blackscholes::calculate_pricing_Put(S,K,r,sigma,T);
                f = BS - market_price;
                v = vega::calculate_vega(S,K,r,sigma,T)*100;
                sigma = sigma - (f/v);
            }
            cout << "BS : " << BS << " f: " << f << " v : " << v << " sigma : " << sigma << endl;
        }
        return sigma;
    }
}