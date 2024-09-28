#ifndef VLE_H
#define VLE_H

#include <vector>
#include "Component.h"

class VLE {
public:
    std::vector<double> calculateKValues(const std::vector<Component>& components, double temperature, double pressure);

    // placeholder for more VLE models
};

#endif // VLE_H