#include <iostream>
using namespace std;
#include "normalDistribution.h"

int main(){
    normalDistribution::genererNombreDefaut();
    normalDistribution::genererNombre(30.0, 8.0);
    double n = normalDistribution::normalCDF(2);
    cout << n << endl;
    return 0;
}