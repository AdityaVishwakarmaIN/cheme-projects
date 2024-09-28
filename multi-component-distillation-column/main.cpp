#include <iostream>
#include "Column.h"
#include "Solver.h"
#include "Component.h"

int main() {
    std::vector<Component> components = {
        Component("Methanol", 32.04, 8.08097, 1582.271, 239.726),
        Component("Ethanol", 46.07, 8.20417, 1642.89, 230.300),
        Component("Water", 18.015, 8.07131, 1730.63, 233.426)
    };

    int numberOfStages = 10;
    Column column(numberOfStages, components);

    double refluxRatio = 1.5;
    double reboilerDuty = 5000.0; 

    double D = 100.0;
    std::vector<double> yD = {0.8, 0.15, 0.05}; 

    double F = 100.0; 
    std::vector<double> zF = {0.5, 0.3, 0.2}; 

    int feedStage = 5;
    double feedTemperature = 78.0; 

    column.setBoundaryConditions(refluxRatio, reboilerDuty, D, yD, F, zF, feedStage, feedTemperature);

    Solver solver(column, 1e-6, 1000);

    if (solver.solve()) {
        std::cout << "Solution converged successfully." << std::endl;
        // implement after professor consult
    } else {
        std::cout << "Solver did not converge within the maximum iterations." << std::endl;
    }

    return 0;
}