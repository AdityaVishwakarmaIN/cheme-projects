#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include "Component.h"

class Stage {
public:
    int stageNumber;
    double temperature;
    double pressure;
    double liquidFlowRate;
    double vaporFlowRate;
    std::vector<double> liquidComposition; // x_i
    std::vector<double> vaporComposition;  // y_i

    Stage(int number, int numComponents);

    void updateCompositions(const std::vector<double>& K_values);

    void normalizeCompositions();
};

#endif