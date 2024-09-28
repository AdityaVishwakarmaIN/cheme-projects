#ifndef SOLVER_H
#define SOLVER_H

#include "Grid3D.h"
#include "VectorField3D.h"
#include "ScalarField3D.h"
#include "SparseMatrix.h"
#include "Constants.h"
#include <vector>

class Solver {
private:
    Grid3D& grid;
    VectorField3D& velocity;
    ScalarField3D& pressure;
    double convergenceCriteria;
    int maxIterations;
    int currentIteration;
    
    VectorField3D predictedVelocity;
    ScalarField3D pressureCorrection;
    
public:
    Solver(Grid3D& grid_, VectorField3D& velocity_, ScalarField3D& pressure_);

    void iterate();
    bool hasConverged() const;
    int getIteration() const;
};

#endif