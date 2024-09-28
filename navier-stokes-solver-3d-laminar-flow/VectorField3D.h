#ifndef VECTORFIELD3D_H
#define VECTORFIELD3D_H

#include "Grid3D.h"
#include <vector>

class VectorField3D {
public:
    Grid3D& grid;
    std::vector<double> u, v, w;

    VectorField3D(Grid3D& grid_);
    double getU(int i, int j, int k) const;
    double getV(int i, int j, int k) const;
    double getW(int i, int j, int k) const;

    void setU(int i, int j, int k, double value);
    void setV(int i, int j, int k, double value);
    void setW(int i, int j, int k, double value);
};

#endif