#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
public:
    std::string name;
    double molecularWeight;
    double antoineA;
    double antoineB;
    double antoineC;

    Component(const std::string& name, double mw, double A, double B, double C);

    double getSaturationPressure(double temperature) const;
};

#endif