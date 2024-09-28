#include "Column.h"

Column::Column(int stages, const std::vector<Component>& comps)
    : numberOfStages(stages), refluxRatio(0.0), reboilerDuty(0.0),
      components(comps), stages(), distillateFlowRate(0.0),
      distillateComposition(comps.size(), 0.0), feedFlowRate(0.0),
      feedComposition(comps.size(), 0.0), feedStage(0), feedTemperature(0.0) {
    initializeStages();
}

void Column::initializeStages() {
    for (int i = 1; i <= numberOfStages; ++i) {
        stages.emplace_back(Stage(i, components.size()));
        // Set default pressure and temperature if needed
        stages.back().pressure = 101.325; 
        stages.back().temperature = 78.0;
    }
}

void Column::setBoundaryConditions(double reflux, double reboiler, 
                                   double D, const std::vector<double>& yD,
                                   double F, const std::vector<double>& zF,
                                   int feedStg, double TF) {
    refluxRatio = reflux;
    reboilerDuty = reboiler;
    distillateFlowRate = D;
    distillateComposition = yD;
    feedFlowRate = F;
    feedComposition = zF;
    feedStage = feedStg;
    feedTemperature = TF;

    if(feedStage > 0 && feedStage <= numberOfStages) {
        stages[feedStage - 1].liquidFlowRate = F;
        stages[feedStage - 1].temperature = TF;
        for(size_t i = 0; i < components.size(); ++i) {
            stages[feedStage - 1].liquidComposition[i] = zF[i];
        }
    }
}