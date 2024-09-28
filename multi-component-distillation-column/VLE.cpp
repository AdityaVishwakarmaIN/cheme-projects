#include "VLE.h"
#include <cmath>

std::vector<double> VLE::calculateKValues(const std::vector<Component>& components, double temperature, double pressure) {
    std::vector<double> K_values;
    for (const auto& comp : components) {
        double P_sat = comp.getSaturationPressure(temperature);
        double P_total = pressure * 7.50062;
        double K = P_sat / P_total;
        K_values.push_back(K);
    }
    return K_values;
}