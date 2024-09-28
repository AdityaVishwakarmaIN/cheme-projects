#include "Solver.h"
#include "BoundaryConditions.h"
#include <cmath>
#include <iostream>

Solver::Solver(Grid3D& grid_, VectorField3D& velocity_, ScalarField3D& pressure_)
    : grid(grid_), velocity(velocity_), pressure(pressure_),
      convergenceCriteria(Constants::tolerance),
      maxIterations(Constants::maxIterations),
      currentIteration(0),
      predictedVelocity(grid),
      pressureCorrection(grid) {
}

void Solver::iterate() {
    for (int k = 1; k < grid.nz - 1; ++k) {
        for (int j = 1; j < grid.ny - 1; ++j) {
            for (int i = 1; i < grid.nx - 1; ++i) {
                int index = grid.getIndex(i, j, k);
                double u_star = velocity.getU(i, j, k); // Placeholder: Update with actual discretization
                // Add convective, diffusive, and pressure gradient terms
                predictedVelocity.setU(i, j, k, u_star);
            }
        }
    }

    int size = grid.getTotalPoints();
    SparseMatrix A(size);
    std::vector<double> b_vec(size, 0.0);

    for (int k = 1; k < grid.nz - 1; ++k) {
        for (int j = 1; j < grid.ny - 1; ++j) {
            for (int i = 1; i < grid.nx - 1; ++i) {
                int idx = grid.getIndex(i, j, k);
                
                double div = (predictedVelocity.getU(i + 1, j, k) - predictedVelocity.getU(i - 1, j, k)) / (2 * grid.dx)
                           + (predictedVelocity.getV(i, j + 1, k) - predictedVelocity.getV(i, j - 1, k)) / (2 * grid.dy)
                           + (predictedVelocity.getW(i, j, k + 1) - predictedVelocity.getW(i, j, k - 1)) / (2 * grid.dz);
                
                A.addValue(idx, idx, -6.0); // Example coefficient, adjust based on discretization
                b_vec[idx] = -div;
            }
        }
    }

    A.finalize();

    std::vector<double> p_prime(size, 0.0);
    std::vector<double> residual(size, 0.0);
    bool converged = false;
    int iter = 0;
    double omega = 1.0; // Relaxation factor

    while (!converged && iter < maxIterations) {
        for (int i = 0; i < size; ++i) {
            double sum = 0.0;
            for (int idx = A.rowPtr[i]; idx < A.rowPtr[i + 1]; ++idx) {
                int col = A.colIndices[idx];
                if (col != i) {
                    sum += A.values[idx] * p_prime[col];
                }
            }
            p_prime[i] = (b_vec[i] - sum) / A.values[A.rowPtr[i + 1] - 1];
        }

        double res = 0.0;
        for (int i = 0; i < size; ++i) {
            double sum = 0.0;
            for (int idx = A.rowPtr[i]; idx < A.rowPtr[i + 1]; ++idx) {
                int col = A.colIndices[idx];
                sum += A.values[idx] * p_prime[col];
            }
            residual[i] = std::abs(b_vec[i] - sum);
            res = std::max(res, residual[i]);
        }

        if (res < convergenceCriteria) {
            converged = true;
        }

        iter++;
    }

    for (int i = 0; i < size; ++i) {
        pressure.p[i] += p_prime[i];
    }

    for (int k = 1; k < grid.nz - 1; ++k) {
        for (int j = 1; j < grid.ny - 1; ++j) {
            for (int i = 1; i < grid.nx - 1; ++i) {
                double delta_p = (pressure.p[grid.getIndex(i + 1, j, k)] - pressure.p[grid.getIndex(i - 1, j, k)]) / (2 * grid.dx);
                velocity.u[grid.getIndex(i, j, k)] = predictedVelocity.getU(i, j, k) + (Constants::dt / Constants::rho) * delta_p;

                double delta_p_v = (pressure.p[grid.getIndex(i, j + 1, k)] - pressure.p[grid.getIndex(i, j - 1, k)]) / (2 * grid.dy);
                velocity.v[grid.getIndex(i, j, k)] = predictedVelocity.getV(i, j, k) + (Constants::dt / Constants::rho) * delta_p_v;
                
                double delta_p_w = (pressure.p[grid.getIndex(i, j, k + 1)] - pressure.p[grid.getIndex(i, j, k - 1)]) / (2 * grid.dz);
                velocity.w[grid.getIndex(i, j, k)] = predictedVelocity.getW(i, j, k) + (Constants::dt / Constants::rho) * delta_p_w;
            }
        }
    }

    currentIteration++;
}

bool Solver::hasConverged() const {
    return currentIteration >= maxIterations;
}

int Solver::getIteration() const {
    return currentIteration;
}