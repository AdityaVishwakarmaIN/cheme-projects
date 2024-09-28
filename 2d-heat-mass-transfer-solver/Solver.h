#ifndef SOLVER_H
#define SOLVER_H

#include "Grid2D.h"
#include "ScalarField2D.h"

class Solver {
public:
    Solver(double rho, double cp, double k, double D, double Q, double R,
           Grid2D& grid, ScalarField2D& temperature, ScalarField2D& concentration,
           double dt);

    void advanceTimeStep();

private:
    double rho, cp, k, D, Q, R;
    Grid2D& grid;
    ScalarField2D& temperature;
    ScalarField2D& concentration;
    double dt;

    void explicitStep();
    // consult prof for following steps
    // void implicitStep();
    // void crankNicolsonStep();
};

#endif