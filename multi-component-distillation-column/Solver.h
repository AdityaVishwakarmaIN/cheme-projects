#ifndef SOLVER_H
#define SOLVER_H

#include "Column.h"

class Solver {
public:
    Column& column;
    double tolerance;
    int maxIterations;
    Solver(Column& col, double tol = 1e-6, int maxIters = 1000);
    bool solve();

private:
    double calculateError(const std::vector<double>& variables);
    void calculateResiduals(const std::vector<double>& variables, std::vector<double>& residuals);
    void calculateJacobian(const std::vector<double>& variables, std::vector<std::vector<double>>& Jacobian);
};

#endif