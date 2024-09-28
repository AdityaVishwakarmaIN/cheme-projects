#ifndef SCALARFIELD2D_H
#define SCALARFIELD2D_H

#include <vector>
#include "Grid2D.h"

class ScalarField2D {
public:
    Grid2D& grid;
    std::vector<double> field; // 1D representation of 2D field

    ScalarField2D(Grid2D& grid);

    // Accessor methods
    double& at(int i, int j);
    const double& at(int i, int j) const;
};

#endif