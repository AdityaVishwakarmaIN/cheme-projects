#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H

#include "ScalarField2D.h"

class BoundaryConditions {
public:
    void applyDirichletTemperature(ScalarField2D& temperature, double T_wall);

    void applyNeumannConcentration(ScalarField2D& concentration);
};

#endif