#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include "Stage.h"
#include "Component.h"

class Column {
public:
    int numberOfStages;
    double refluxRatio;
    double reboilerDuty;
    std::vector<Component> components;
    std::vector<Stage> stages;

    double distillateFlowRate;
    std::vector<double> distillateComposition;
    double feedFlowRate;
    std::vector<double> feedComposition;
    int feedStage;
    double feedTemperature;

    Column(int stages, const std::vector<Component>& comps);

    void initializeStages();

    void setBoundaryConditions(double reflux, double reboiler, 
                               double D, const std::vector<double>& yD,
                               double F, const std::vector<double>& zF,
                               int feedStg, double TF);
};

#endif