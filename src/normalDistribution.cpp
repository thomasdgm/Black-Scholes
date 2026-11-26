#include <iostream>
#include <random>
#include <cmath>
#include "normalDistribution.h"
using namespace std;

constexpr double PI = 3.14159265358979323846;

namespace normalDistribution{
    double genererNombreDefaut(){
        double average = 50.0;
        double deviationType = 10.0;
        static std::mt19937 gen(std::random_device{}());
        std::normal_distribution<double> d(average, deviationType);
        double nbr = d(gen);
        cout << "Number to generate randomly : " << nbr << endl;
        return nbr;
    }

    double genererNombre(double const average, double const deviationType){
        static std::mt19937 gen(std::random_device{}());
        std::normal_distribution<double> d(average, deviationType);
        double nbr = d(gen);
        cout << "Number to generate randomly : " << nbr << endl;
        return nbr;
    }

    double normalCDF(double const x){
        return 0.5 * std::erfc(-x/std::sqrt(2.0));
    }

    double densite(double const x){
        return (1.0 / (sqrt(2 * PI)) * exp(-0.5 * x * x));
    }
}
