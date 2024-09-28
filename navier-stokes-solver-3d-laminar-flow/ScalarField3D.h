#ifndef SCALARFIELD3D_H
#define SCALARFIELD3D_H

#include "Grid3D.h"
#include <vector>

class ScalarField3D {
public:
    Grid3D& grid;
    std::vector<double> p;

    ScalarField3D(Grid3D& grid_);
    double getP(int i, int j, int k) const;
    void setP(int i, int j, int k, double value);
};

#endif