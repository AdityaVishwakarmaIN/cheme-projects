#ifndef UTILITIES_H
#define UTILITIES_H

#include "VectorField3D.h"
#include "ScalarField3D.h"
#include "Grid3D.h"

class Utilities {
public:
    static void initializeFields(VectorField3D& velocity, ScalarField3D& pressure, const Grid3D& grid);
    static void outputFields(const VectorField3D& velocity, const ScalarField3D& pressure, const Grid3D& grid, int iteration);
};

#endif