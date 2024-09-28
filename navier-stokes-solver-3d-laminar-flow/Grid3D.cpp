#include "Grid3D.h"

Grid3D::Grid3D(int nx_, int ny_, int nz_, double dx_, double dy_, double dz_)
    : nx(nx_), ny(ny_), nz(nz_), dx(dx_), dy(dy_), dz(dz_) {
    // implement after prof consult
}

int Grid3D::getTotalPoints() const {
    return nx * ny * nz;
}

int Grid3D::getIndex(int i, int j, int k) const {
    return i + nx * (j + ny * k);
}
