#include "Component.h"
#include <cmath>

Component::Component(const std::string& name, double mw, double A, double B, double C)
    : name(name), molecularWeight(mw), antoineA(A), antoineB(B), antoineC(C) {}

double Component::getSaturationPressure(double temperature) const {
    return pow(10, antoineA - (antoineB / (antoineC + temperature)));
}