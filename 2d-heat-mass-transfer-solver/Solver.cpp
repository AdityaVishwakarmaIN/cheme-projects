#include "Solver.h"
#include <vector>
#include <stdexcept>

Solver::Solver(double rho, double cp, double k, double D, double Q, double R,
               Grid2D& grid, ScalarField2D& temperature, ScalarField2D& concentration,
               double dt)
    : rho(rho), cp(cp), k(k), D(D), Q(Q), R(R),
      grid(grid), temperature(temperature), concentration(concentration),
      dt(dt) {
    // intialize after prof consult
}

void Solver::advanceTimeStep() {
    explicitStep();
    // May use Implicit or Crank-Nicolson but not implemented right now
}

void Solver::explicitStep() {
    std::vector<double> newTemp = temperature.field;
    std::vector<double> newConc = concentration.field;

    double alpha = k / (rho * cp);
    double beta = D;

    for(int i = 1; i < grid.nx - 1; ++i) {
        for(int j = 1; j < grid.ny - 1; ++j) {
            double d2T_dx2 = (temperature.at(i+1, j) - 2.0 * temperature.at(i, j) + temperature.at(i-1, j)) / (grid.dx * grid.dx);
            double d2T_dy2 = (temperature.at(i, j+1) - 2.0 * temperature.at(i, j) + temperature.at(i, j-1)) / (grid.dy * grid.dy);
            newTemp[i * grid.ny + j] = temperature.at(i, j) + dt * (alpha * (d2T_dx2 + d2T_dy2) + Q / (rho * cp));
        }
    }

    for(int i = 1; i < grid.nx - 1; ++i) {
        for(int j = 1; j < grid.ny - 1; ++j) {
            double d2C_dx2 = (concentration.at(i+1, j) - 2.0 * concentration.at(i, j) + concentration.at(i-1, j)) / (grid.dx * grid.dx);
            double d2C_dy2 = (concentration.at(i, j+1) - 2.0 * concentration.at(i, j) + concentration.at(i, j-1)) / (grid.dy * grid.dy);
            newConc[i * grid.ny + j] = concentration.at(i, j) + dt * (beta * (d2C_dx2 + d2C_dy2) + R);
        }
    }

    temperature.field = newTemp;
    concentration.field = newConc;
}