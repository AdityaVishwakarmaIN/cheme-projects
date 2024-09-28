#include <iostream>
#include <cmath>
#include "Grid2D.h"
#include "ScalarField2D.h"
#include "BoundaryConditions.h"
#include "Solver.h"
#include "Utils.h"

int main() {
    double rho = 1.0;          // Density (kg/m^3)
    double cp = 1.0;           // Specific heat (J/(kg·K))
    double k = 1.0;            // Thermal conductivity (W/(m·K))
    double D = 0.1;            // Diffusion coefficient (m^2/s)
    double Q = 0.0;            // Heat source term (W/m^3)
    double R = 0.0;            // Mass source/sink term (kg/(m^3·s))
    double dx = 0.01;          // Grid spacing in x (m)
    double dy = 0.01;          // Grid spacing in y (m)
    double dt = 0.0001;        // Time step (s)
    int nx = 50;               // Number of grid points in x
    int ny = 50;               // Number of grid points in y
    int maxTimeSteps = 1000;   // Maximum number of time steps

    Grid2D grid(nx, ny, dx, dy);

    ScalarField2D temperature(grid);
    ScalarField2D concentration(grid);

    double ambientTemp = 300.0; 
    int hotspot_i = nx / 2;
    int hotspot_j = ny / 2;
    double hotspotTemp = 500.0; 
    Utils::initializeTemperature(temperature, ambientTemp, hotspot_i, hotspot_j, hotspotTemp);

    double initialConc = 0.0;    
    int source_i = nx / 4;
    int source_j = ny / 4;
    double sourceConc = 1.0;          
    Utils::initializeConcentration(concentration, initialConc, source_i, source_j, sourceConc);

    BoundaryConditions bc;
    double T_wall = ambientTemp; // Dirichlet boundary condition value
    bc.applyDirichletTemperature(temperature, T_wall);
    bc.applyNeumannConcentration(concentration);

    Solver solver(rho, cp, k, D, Q, R, grid, temperature, concentration, dt);

    for(int step = 0; step < maxTimeSteps; ++step) {
        solver.advanceTimeStep();

        bc.applyDirichletTemperature(temperature, T_wall);
        bc.applyNeumannConcentration(concentration);

        if(step % 100 == 0) {
            Utils::exportData(temperature, concentration, step);
            std::cout << "Step " << step << " completed.\n";
        }
    }

    Utils::exportData(temperature, concentration, maxTimeSteps);
    std::cout << "Simulation completed. Data exported for visualization.\n";

    // Utils::visualizeResults();

    return 0;
}