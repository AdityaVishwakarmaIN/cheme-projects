#include "SparseMatrix.h"
#include <algorithm>
#include <unordered_map>

SparseMatrix::SparseMatrix(int size_) : size(size_) {
    rowPtr.reserve(size + 1);
    rowPtr.push_back(0);
}

void SparseMatrix::addValue(int row, int col, double value) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Row or column index out of range.");
    }
    colIndices.push_back(col);
    values.push_back(value);
}

std::vector<double> SparseMatrix::multiply(const std::vector<double>& vec) const {
    if (vec.size() != size) {
        throw std::invalid_argument("Vector size does not match matrix dimensions.");
    }
    std::vector<double> result(size, 0.0);
    for (int i = 0; i < size; ++i) {
        for (int idx = rowPtr[i]; idx < rowPtr[i + 1]; ++idx) {
            result[i] += values[idx] * vec[colIndices[idx]];
        }
    }
    return result;
}

}
