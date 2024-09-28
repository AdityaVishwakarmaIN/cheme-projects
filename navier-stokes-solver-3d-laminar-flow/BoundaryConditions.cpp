#include "BoundaryConditions.h"

void BoundaryConditions::apply(VectorField3D& velocity, ScalarField3D& pressure, const Grid3D& grid) {
    for (int k = 0; k < grid.nz; ++k) {
        for (int j = 0; j < grid.ny; ++j) {
            velocity.setU(0, j, k, 1.0); // fixed inlet velocity
            velocity.setV(0, j, k, 0.0);
            velocity.setW(0, j, k, 0.0);

            velocity.setU(j, 0, k, 0.0);
            velocity.setV(j, 0, k, 0.0);
            velocity.setW(j, 0, k, 0.0);

            velocity.setU(j, grid.ny - 1, k, 0.0);
            velocity.setV(j, grid.ny - 1, k, 0.0);
            velocity.setW(j, grid.ny - 1, k, 0.0);
        }
    }

    for (int j = 0; j < grid.ny; ++j) {
        for (int k = 0; k < grid.nz; ++k) {
            int i = grid.nx - 1;
            int index = grid.getIndex(i, j, k);
            // to implement pressure Neumann condition: dp/dx = 0
        }
    }
}