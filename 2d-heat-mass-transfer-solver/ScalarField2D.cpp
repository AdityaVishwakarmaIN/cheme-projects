#include "ScalarField2D.h"
#include <stdexcept>

ScalarField2D::ScalarField2D(Grid2D& grid)
    : grid(grid), field(grid.nx * grid.ny, 0.0) {
    // to initialize after prof consult
}

double& ScalarField2D::at(int i, int j) {
    if(i < 0 || i >= grid.nx || j < 0 || j >= grid.ny) {
        throw std::out_of_range("Index out of bounds in ScalarField2D::at()");
    }
    return field[i * grid.ny + j];
}

const double& ScalarField2D::at(int i, int j) const {
    if(i < 0 || i >= grid.nx || j < 0 || j >= grid.ny) {
        throw std::out_of_range("Index out of bounds in ScalarField2D::at() const");
    }
    return field[i * grid.ny + j];
}