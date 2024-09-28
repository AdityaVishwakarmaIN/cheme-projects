#include "ScalarField3D.h"

ScalarField3D::ScalarField3D(Grid3D& grid_) : grid(grid_),
    p(grid.getTotalPoints(), 0.0) {
    // implement after prof consult pressure not needed
}

double ScalarField3D::getP(int i, int j, int k) const {
    int index = grid.getIndex(i, j, k);
    return p[index];
}

void ScalarField3D::setP(int i, int j, int k, double value) {
    int index = grid.getIndex(i, j, k);
    p[index] = value;
}
