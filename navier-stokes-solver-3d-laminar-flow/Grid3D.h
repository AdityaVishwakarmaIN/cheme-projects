#ifndef GRID3D_H
#define GRID3D_H

class Grid3D {
public:
    int nx, ny, nz;
    double dx, dy, dz;      

    Grid3D(int nx_, int ny_, int nz_, double dx_, double dy_, double dz_);

    int getTotalPoints() const;
    int getIndex(int i, int j, int k) const;
};

#endif