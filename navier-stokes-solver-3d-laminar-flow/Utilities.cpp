#include "Utilities.h"
#include <fstream>
#include <iomanip>

void Utilities::initializeFields(VectorField3D& velocity, ScalarField3D& pressure, const Grid3D& grid) {
    for (int i = 0; i < grid.getTotalPoints(); ++i) {
        velocity.u[i] = 0.0;
        velocity.v[i] = 0.0;
        velocity.w[i] = 0.0;
        pressure.p[i] = 0.0;
    }
}

void Utilities::outputFields(const VectorField3D& velocity, const ScalarField3D& pressure, const Grid3D& grid, int iteration) {
    std::ofstream velFile("velocity_" + std::to_string(iteration) + ".vtk");
    std::ofstream presFile("pressure_" + std::to_string(iteration) + ".vtk");

    if (!velFile.is_open() || !presFile.is_open()) {
        throw std::runtime_error("Unable to open output files.");
    }

    velFile << "# vtk DataFile Version 3.0\n";
    velFile << "Velocity field\n";
    velFile << "ASCII\n";
    velFile << "DATASET STRUCTURED_POINTS\n";
    velFile << "DIMENSIONS " << grid.nx << " " << grid.ny << " " << grid.nz << "\n";
    velFile << "ORIGIN 0 0 0\n";
    velFile << "SPACING " << grid.dx << " " << grid.dy << " " << grid.dz << "\n";
    velFile << "POINT_DATA " << grid.getTotalPoints() << "\n";
    velFile << "VECTORS velocity float\n";
    for (int i = 0; i < grid.getTotalPoints(); ++i) {
        velFile << velocity.u[i] << " " << velocity.v[i] << " " << velocity.w[i] << "\n";
    }

    presFile << "# vtk DataFile Version 3.0\n";
    presFile << "Pressure field\n";
    presFile << "ASCII\n";
    presFile << "DATASET STRUCTURED_POINTS\n";
    presFile << "DIMENSIONS " << grid.nx << " " << grid.ny << " " << grid.nz << "\n";
    presFile << "ORIGIN 0 0 0\n";
    presFile << "SPACING " << grid.dx << " " << grid.dy << " " << grid.dz << "\n";
    presFile << "POINT_DATA " << grid.getTotalPoints() << "\n";
    presFile << "SCALARS pressure float 1\n";
    presFile << "LOOKUP_TABLE default\n";
    for (int i = 0; i < grid.getTotalPoints(); ++i) {
        presFile << pressure.p[i] << "\n";
    }

    velFile.close();
    presFile.close();
}
