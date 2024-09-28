#include "Utility.h"
#include <numeric>
#include <cmath>
#include <iostream>

void normalize(std::vector<double>& vec) {
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    if (sum != 0.0) {
        for (auto& val : vec) {
            val /= sum;
        }
    } else {
        double equal = 1.0 / vec.size();
        for (auto& val : vec) {
            val = equal;
        }
    }
}

bool solveLinearSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double>& x) {
    int n = A.size();

    std::vector<std::vector<double>> augmented(n, std::vector<double>(n + 1, 0.0));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            augmented[i][j] = A[i][j];
        }
        augmented[i][n] = -b[i];
    }

    for(int i = 0; i < n; ++i){
        double maxElement = std::abs(augmented[i][i]);
        int maxRow = i;
        for(int k = i+1; k < n; ++k){
            if(std::abs(augmented[k][i]) > maxElement){
                maxElement = std::abs(augmented[k][i]);
                maxRow = k;
            }
        }

        if(maxRow != i){
            std::swap(augmented[i], augmented[maxRow]);
        }

        if(std::abs(augmented[i][i]) < 1e-12){
            std::cerr << "Matrix is singular or nearly singular!" << std::endl;
            return false;
        }

        for(int k = i+1; k < n; ++k){
            double factor = augmented[k][i] / augmented[i][i];
            for(int j = i; j < n+1; ++j){
                augmented[k][j] -= factor * augmented[i][j];
            }
        }
    }

    x.assign(n, 0.0);
    for(int i = n-1; i >=0; --i){
        double sum = 0.0;
        for(int j = i+1; j < n; ++j){
            sum += augmented[i][j] * x[j];
        }
        x[i] = (augmented[i][n] - sum) / augmented[i][i];
    }

    return true;
}