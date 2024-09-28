#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
void normalize(std::vector<double>& vec);
bool solveLinearSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double>& x);

#endif