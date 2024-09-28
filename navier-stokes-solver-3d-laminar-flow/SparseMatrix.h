#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <stdexcept>

class SparseMatrix {
public:
    int size;
    std::vector<int> rowPtr;
    std::vector<int> colIndices;
    std::vector<double> values;

    SparseMatrix(int size_);

    void addValue(int row, int col, double value);
    std::vector<double> multiply(const std::vector<double>& vec) const;
    void finalize();
};

#endif