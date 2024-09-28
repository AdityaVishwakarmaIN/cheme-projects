#include "BoundaryConditions.h"

void BoundaryConditions::applyDirichletTemperature(ScalarField2D& temperature, double T_wall) {
    Grid2D& grid = temperature.grid;

    for(int j = 0; j < grid.ny; ++j) {
        temperature.at(0, j) = T_wall;
        temperature.at(grid.nx - 1, j) = T_wall;
    }

    for(int i = 0; i < grid.nx; ++i) {
        temperature.at(i, 0) = T_wall;
        temperature.at(i, grid.ny - 1) = T_wall;
    }
}

void BoundaryConditions::applyNeumannConcentration(ScalarField2D& concentration) {
    Grid2D& grid = concentration.grid;

    // Left boundary (i = 0)
    for(int j = 0; j < grid.ny; ++j) {
        concentration.at(0, j) = concentration.at(1, j);
    }

    // Right boundary (i = nx-1)
    for(int j = 0; j < grid.ny; ++j) {
        concentration.at(grid.nx - 1, j) = concentration.at(grid.nx - 2, j);
    }

    // Top boundary (j = 0)
    for(int i = 0; i < grid.nx; ++i) {
        concentration.at(i, 0) = concentration.at(i, 1);
    }

    // Bottom boundary (j = ny-1)
    for(int i = 0; i < grid.nx; ++i) {
        concentration.at(i, grid.ny - 1) = concentration.at(i, grid.ny - 2);
    }
}