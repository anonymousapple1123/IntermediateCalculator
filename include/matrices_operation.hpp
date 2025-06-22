#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <cmath>

template<typename T>
class MatrixOperation {
    static_assert(std::is_floating_point<T>::value, "MatrixOperation only supports floating-point types.");

private:
    std::vector<std::vector<T>> matrix;

public:
    MatrixOperation(const std::vector<std::vector<T>>& matrix)
        : matrix(matrix) {}


    std::vector<std::vector<T>> operator+(const MatrixOperation<T>& matrix_2);
    std::vector<std::vector<T>> operator-(const MatrixOperation<T>& matrix_2);
    std::vector<std::vector<T>> operator*(const MatrixOperation<T>& matrix_2);

    void PrintMatrix() const ;
    bool isequal(MatrixOperation<T>& matrix_2) const;
    void isequal_v(const std::vector<std::vector<T>>& m2) const;
    std::vector<std::vector<T>> Transpose();
    std::vector<std::vector<T>> ScalarMultiply(T scalar);
    T Determinant();
    std::vector<std::vector<T>> Inverse();
};
