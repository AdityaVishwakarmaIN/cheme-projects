#include "Grid3D.h"
#include "VectorField3D.h"
#include "ScalarField3D.h"
#include "BoundaryConditions.h"
#include "Solver.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>

int main() {
    try {
        int nx = 50;
        int ny = 50;
        int nz = 50;
        double dx = 1.0 / (nx - 1);
        double dy = 1.0 / (ny - 1);
        double dz = 1.0 / (nz - 1);

        Grid3D grid(nx, ny, nz, dx, dy, dz);
        VectorField3D velocity(grid);
        ScalarField3D pressure(grid);

        Utilities::initializeFields(velocity, pressure, grid);
        BoundaryConditions::apply(velocity, pressure, grid);
        Solver solver(grid, velocity, pressure);

        while (!solver.hasConverged()) {
            solver.iterate();
            BoundaryConditions::apply(velocity, pressure, grid);

            if (solver.getIteration() % 100 == 0) {
                Utilities::outputFields(velocity, pressure, grid, solver.getIteration());
                std::cout << "Iteration: " << solver.getIteration() << std::endl;
            }
        }

        Utilities::outputFields(velocity, pressure, grid, solver.getIteration());
        std::cout << "Simulation completed after " << solver.getIteration() << " iterations." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}