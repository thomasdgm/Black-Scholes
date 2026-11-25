#ifndef _NORMALDISTRIBUTION_H
#define _NORMALDISTRIBUTION_H

namespace normalDistribution {
    double genererNombreDefaut();

    double genererNombre(double const average, double const deviationType);

    double normalCDF(double const x);

    double densite(double const x);
}



#endif