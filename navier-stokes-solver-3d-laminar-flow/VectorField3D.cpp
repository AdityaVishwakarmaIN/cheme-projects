#include "VectorField3D.h"

VectorField3D::VectorField3D(Grid3D& grid_) : grid(grid_),
    u(grid.getTotalPoints(), 0.0),
    v(grid.getTotalPoints(), 0.0),
    w(grid.getTotalPoints(), 0.0) {
    // project report doesnt specify ask prof
}

double VectorField3D::getU(int i, int j, int k) const {
    int index = grid.getIndex(i, j, k);
    return u[index];
}

double VectorField3D::getV(int i, int j, int k) const {
    int index = grid.getIndex(i, j, k);
    return v[index];
}

double VectorField3D::getW(int i, int j, int k) const {
    int index = grid.getIndex(i, j, k);
    return w[index];
}

void VectorField3D::setU(int i, int j, int k, double value) {
    int index = grid.getIndex(i, j, k);
    u[index] = value;
}

void VectorField3D::setV(int i, int j, int k, double value) {
    int index = grid.getIndex(i, j, k);
    v[index] = value;
}

void VectorField3D::setW(int i, int j, int k, double value) {
    int index = grid.getIndex(i, j, k);
    w[index] = value;
}