#include "Stage.h"
#include "Utility.h"

Stage::Stage(int number, int numComponents)
    : stageNumber(number), temperature(0.0), pressure(0.0),
      liquidFlowRate(0.0), vaporFlowRate(0.0),
      liquidComposition(numComponents, 0.0),
      vaporComposition(numComponents, 0.0) {}

void Stage::updateCompositions(const std::vector<double>& K_values) {
    for (size_t i = 0; i < liquidComposition.size(); ++i) {
        vaporComposition[i] = K_values[i] * liquidComposition[i];
    }
    normalizeCompositions();
}

void Stage::normalizeCompositions() {
    normalize(vaporComposition);
}