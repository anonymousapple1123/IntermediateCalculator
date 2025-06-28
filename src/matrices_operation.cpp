#include "matrices_operation.hpp"

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::operator+(const MatrixOperation<T>& matrix_2) {
    if (matrix.size() != matrix_2.matrix.size() || matrix[0].size() != matrix_2.matrix[0].size())
        throw std::runtime_error("Matrices must have the same dimensions for addition.");

    std::vector<std::vector<T>> result = matrix;

    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix[i].size(); ++j)
            result[i][j] += matrix_2.matrix[i][j];

    return result;
}

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::operator-(const MatrixOperation<T>& matrix_2) {
    if (matrix.size() != matrix_2.matrix.size() || matrix[0].size() != matrix_2.matrix[0].size())
        throw std::runtime_error("Matrices must have the same dimensions for subtraction.");

    std::vector<std::vector<T>> result = matrix;

    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix[i].size(); ++j)
            result[i][j] -= matrix_2.matrix[i][j];

    return result;
}

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::operator*(const MatrixOperation<T>& matrix_2) {
    if (matrix[0].size() != matrix_2.matrix.size())
        throw std::runtime_error("Matrix multiplication not possible with given dimensions.");

    size_t rows = matrix.size();
    size_t cols = matrix_2.matrix[0].size();
    size_t inner = matrix[0].size();

    std::vector<std::vector<T>> result(rows, std::vector<T>(cols, 0));

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            for (size_t k = 0; k < inner; ++k)
                result[i][j] += matrix[i][k] * matrix_2.matrix[k][j];

    return result;
}

template<typename T>
void MatrixOperation<T>::PrintMatrix() const {
    for (const auto& row : matrix) {
        for (const auto& val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
}

template<typename T>
bool MatrixOperation<T>::isequal(MatrixOperation<T>& matrix_2) const {
    if (matrix.size() != matrix_2.matrix.size() || matrix[0].size() != matrix_2.matrix[0].size())
        return false;

    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix[i].size(); ++j)
            if (matrix[i][j] != matrix_2.matrix[i][j])
                return false;

    return true;
}

template<typename T>
void MatrixOperation<T>::isequal_v(const std::vector<std::vector<T>>& m2) const {
    bool equal = true;
    if (matrix.size() != m2.size() || matrix[0].size() != m2[0].size()) {
        equal = false;
    } else {
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix[i].size(); ++j)
                if (matrix[i][j] != m2[i][j]) {
                    equal = false;
                    break;
                }
    }

    std::cout << (equal ? "Matrices are equal." : "Matrices are not equal.") << std::endl;
}

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::Transpose() {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    std::vector<std::vector<T>> transposed(cols, std::vector<T>(rows));

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            transposed[j][i] = matrix[i][j];

    return transposed;
}

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::ScalarMultiply(T scalar) {
    std::vector<std::vector<T>> result = matrix;

    for (auto& row : result)
        for (auto& val : row)
            val *= scalar;

    return result;
}

// Helper for Determinant
template<typename T>
T DeterminantHelper(const std::vector<std::vector<T>>& mat) {
    size_t n = mat.size();
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    T det = 0;
    for (size_t p = 0; p < n; ++p) {
        std::vector<std::vector<T>> subMat(n-1, std::vector<T>(n-1));
        for (size_t i = 1; i < n; ++i) {
            size_t colIdx = 0;
            for (size_t j = 0; j < n; ++j) {
                if (j == p) continue;
                subMat[i-1][colIdx++] = mat[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * mat[0][p] * DeterminantHelper(subMat);
    }
    return det;
}

template<typename T>
T MatrixOperation<T>::Determinant() {
    if (matrix.size() != matrix[0].size())
        throw std::runtime_error("Determinant is defined only for square matrices.");

    return DeterminantHelper(matrix);
}

template<typename T>
std::vector<std::vector<T>> MatrixOperation<T>::Inverse() {
    T det = Determinant();
    if (det == 0)
        throw std::runtime_error("Matrix is singular and cannot be inverted.");

    size_t n = matrix.size();
    std::vector<std::vector<T>> inverse(n, std::vector<T>(n, 0));

    // Create the augmented matrix [A | I]
    std::vector<std::vector<T>> aug(n, std::vector<T>(2*n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            aug[i][j] = matrix[i][j];
        }
        aug[i][n+i] = 1;
    }

    // Gauss-Jordan elimination
    for (size_t i = 0; i < n; ++i) {
        T pivot = aug[i][i];
        if (pivot == 0)
            throw std::runtime_error("Matrix is singular and cannot be inverted.");

        for (size_t j = 0; j < 2*n; ++j)
            aug[i][j] /= pivot;

        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                T factor = aug[k][i];
                for (size_t j = 0; j < 2*n; ++j)
                    aug[k][j] -= factor * aug[i][j];
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            inverse[i][j] = aug[i][n + j];

    return inverse;
}

// Explicit instantiations (optional; or move implementation to .hpp)
template class MatrixOperation<float>;
template class MatrixOperation<double>;
template class MatrixOperation<long double>;
