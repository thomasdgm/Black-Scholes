#include <iostream>
using namespace std;
#include <random>
#include <cmath>
#include "normalDistribution.h"

namespace normalDistribution{
    double genererNombreDefaut(){
        double average = 50.0;
        double deviationType = 10.0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> d(average, deviationType);
        double nbr = d(gen);
        cout << "Nombre générer aléatoirement : " << nbr << endl;
        return nbr;
    }

    double genererNombre(double const average, double const deviationType){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> d(average, deviationType);
        double nbr = d(gen);
        cout << "Nombre générer aléatoirement : " << nbr << endl;
        return nbr;
    }

    double normalCDF(double const x){
        return 0.5 * std::erfc(-x/std::sqrt(2.0));
    }

    double densite(double const x){
        return (1/(sqrt(2*M_PI))*exp(-(pow(x,2)/2)));
    }
}
