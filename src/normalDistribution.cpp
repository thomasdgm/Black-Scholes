#include <iostream>
using namespace std;
#include <random>
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

    double normalCDF(double const nombre){
        return 0.5 * std::erfc(-nombre/std::sqrt(2.0));
    }
}
