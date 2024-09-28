#include "Solver.h"
#include "VLE.h"
#include "Utility.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <limits>

Solver::Solver(Column& col, double tol, int maxIters)
    : column(col), tolerance(tol), maxIterations(maxIters) {}

bool Solver::solve() {
    int numStages = column.numberOfStages;
    int numComponents = column.components.size();
    int numVariables = numStages * (2 * numComponents + 2);
	int iteration = 0;
    double error = tolerance + 1.0;

    while (error > tolerance && iteration < maxIterations) {
        std::vector<double> residuals(numVariables, 0.0);
        calculateResiduals(variables, residuals, vleCalculator);

        error = 0.0;
        for (const auto& res : residuals) {
            error = std::max(error, std::abs(res));
        }

        if (error < tolerance) {
            std::cout << "Converged in " << iteration << " iterations with error " << error << std::endl;
            break;
        }

        std::vector<std::vector<double>> Jacobian(numVariables, std::vector<double>(numVariables, 0.0));
        calculateJacobian(variables, Jacobian, vleCalculator);

        std::vector<double> delta;
        bool success = solveLinearSystem(Jacobian, residuals, delta);
        if (!success) {
            std::cerr << "Failed to solve linear system at iteration " << iteration << std::endl;
            return false;
        }

        for (size_t i = 0; i < variables.size(); ++i) {
            variables[i] -= delta[i];
        }

        iteration++;
    }

    if (iteration == maxIterations) {
        std::cerr << "Solver did not converge within the maximum iterations." << std::endl;
        return false;
    }

    mapVariablesToStages(variables, vleCalculator);

    return true;
}

void Solver::mapVariablesToStages(const std::vector<double>& variables, VLE& vleCalculator) {
    int numStages = column.numberOfStages;
    int numComponents = column.components.size();

    for (int stage = 0; stage < numStages; ++stage) {
        int baseIndex = stage * (2 * numComponents + 2);

        for (int comp = 0; comp < numComponents; ++comp) {
            column.stages[stage].liquidComposition[comp] = variables[baseIndex + comp];
        }

        for (int comp = 0; comp < numComponents; ++comp) {
            column.stages[stage].vaporComposition[comp] = variables[baseIndex + numComponents + comp];
        }

        column.stages[stage].liquidFlowRate = variables[baseIndex + 2 * numComponents];

        column.stages[stage].vaporFlowRate = variables[baseIndex + 2 * numComponents + 1];
    }
}

void Solver::calculateResiduals(const std::vector<double>& variables, std::vector<double>& residuals, VLE& vleCalculator) {
    int numStages = column.numberOfStages;
    int numComponents = column.components.size();

    for (int stage = 0; stage < numStages; ++stage) {
        int baseIndex = stage * (2 * numComponents + 2);

        std::vector<double> x_i(numComponents, 0.0);
        std::vector<double> y_i(numComponents, 0.0);
        double L = variables[baseIndex + 2 * numComponents];
        double V = variables[baseIndex + 2 * numComponents + 1];

        for (int comp = 0; comp < numComponents; ++comp) {
            x_i[comp] = variables[baseIndex + comp];
            y_i[comp] = variables[baseIndex + numComponents + comp];
        }

        column.stages[stage].liquidComposition = x_i;
        column.stages[stage].vaporComposition = y_i;
        column.stages[stage].liquidFlowRate = L;
        column.stages[stage].vaporFlowRate = V;

        double T = column.stages[stage].temperature;
        double P = column.stages[stage].pressure;
        std::vector<double> K_values = vleCalculator.calculateKValues(column.components, T, P);

        for (int comp = 0; comp < numComponents; ++comp) {
            double F = (stage == column.feedStage - 1) ? column.feedFlowRate * column.feedComposition[comp] : 0.0;
            double L_next = (stage < numStages - 1) ? variables[((stage + 1) * (2 * numComponents + 2)) + 2 * numComponents] : 0.0;
            double x_next = (stage < numStages - 1) ? variables[((stage + 1) * (2 * numComponents + 2)) + comp] : 0.0;
            double V_prev = (stage > 0) ? variables[((stage - 1) * (2 * numComponents + 2)) + 2 * numComponents + 1] : 0.0;
            double y_prev = (stage > 0) ? variables[((stage - 1) * (2 * numComponents + 2)) + numComponents + comp] : 0.0;

            residuals[baseIndex + comp] = F + L_next * x_next + V_prev * y_prev - L * x_i[comp] - V * y_i[comp];
        }

        for (int comp = 0; comp < numComponents; ++comp) {
            residuals[baseIndex + numComponents + comp] = y_i[comp] - K_values[comp] * x_i[comp];
        }

        double sum_x = 0.0;
        double sum_y = 0.0;
        for (int comp = 0; comp < numComponents; ++comp) {
            sum_x += x_i[comp];
            sum_y += y_i[comp];
        }
        residuals[baseIndex + 2 * numComponents] = sum_x - 1.0; // Sum of x_i = 1
        residuals[baseIndex + 2 * numComponents + 1] = sum_y - 1.0; // Sum of y_i = 1
    }
}

void Solver::calculateJacobian(const std::vector<double>& variables, std::vector<std::vector<double>>& Jacobian, VLE& vleCalculator) {
    double delta = 1e-6; // Small perturbation for finite differences
    int numVariables = variables.size();
    std::vector<double> residuals_base(numVariables, 0.0);

    calculateResiduals(variables, residuals_base, vleCalculator);

    for (int i = 0; i < numVariables; ++i) {
        std::vector<double> variables_perturbed = variables;
        variables_perturbed[i] += delta;

        std::vector<double> residuals_perturbed(numVariables, 0.0);
        calculateResiduals(variables_perturbed, residuals_perturbed, vleCalculator);

        for (int j = 0; j < numVariables; ++j) {
            Jacobian[j][i] = (residuals_perturbed[j] - residuals_base[j]) / delta;
        }
    }
}