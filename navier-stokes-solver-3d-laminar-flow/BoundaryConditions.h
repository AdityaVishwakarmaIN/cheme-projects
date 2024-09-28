#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H

#include "VectorField3D.h"
#include "ScalarField3D.h"

class BoundaryConditions {
public:
    static void apply(VectorField3D& velocity, ScalarField3D& pressure, const Grid3D& grid);
};

#endif