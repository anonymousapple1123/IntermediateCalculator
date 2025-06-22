#include <iostream>
#include <type_traits>
#include <vector>
#include <cmath>

template<typename T>
class MatrixOperation {
    static_assert(std::is_floating_point<T>::value, "MatrixOperation only supports floating-point types.");

private:
    std::vector<std::vector<T>> matrix_1;
    std::vector<std::vector<T>> matrix_2;

public:
    MatrixOperation(const std::vector<std::vector<T>>& mat1, const std::vector<std::vector<T>>& mat2)
        : matrix_1(mat1), matrix_2(mat2) {}

    // Addition
    std::vector<std::vector<T>> AddMatrix() {
        if (!SameSize()) return {};
        size_t rows = matrix_1.size(), cols = matrix_1[0].size();
        std::vector<std::vector<T>> result(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = matrix_1[i][j] + matrix_2[i][j];
        return result;
    }

    // Subtraction
    std::vector<std::vector<T>> SubtractMatrix() {
        if (!SameSize()) return {};
        size_t rows = matrix_1.size(), cols = matrix_1[0].size();
        std::vector<std::vector<T>> result(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = matrix_1[i][j] - matrix_2[i][j];
        return result;
    }

    // Multiplication
    std::vector<std::vector<T>> MultiplyMatrix() {
        if (matrix_1.empty() || matrix_2.empty() || matrix_1[0].size() != matrix_2.size()) {
            PrintMismatch("multiply", matrix_1, matrix_2);
            return {};
        }

        size_t rows = matrix_1.size();
        size_t cols = matrix_2[0].size();
        size_t common = matrix_1[0].size();

        std::vector<std::vector<T>> result(rows, std::vector<T>(cols, 0));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                for (size_t k = 0; k < common; ++k)
                    result[i][j] += matrix_1[i][k] * matrix_2[k][j];
        return result;
    }

    // Transpose
    std::vector<std::vector<T>> TransposeMatrix1() {
        return Transpose(matrix_1);
    }

    std::vector<std::vector<T>> TransposeMatrix2() {
        return Transpose(matrix_2);
    }

    // Scalar Multiplication
    std::vector<std::vector<T>> MultiplyMatrixByScalar1(T scalar) {
        return ScalarMultiply(matrix_1, scalar);
    }

    std::vector<std::vector<T>> MultiplyMatrixByScalar2(T scalar) {
        return ScalarMultiply(matrix_2, scalar);
    }

    // Determinant
    T DeterminantMatrix1() {
        return Determinant2x2(matrix_1);
    }

    T DeterminantMatrix2() {
        return Determinant2x2(matrix_2);
    }

    // Inverse
    std::vector<std::vector<T>> InverseMatrix1() {
        return Inverse2x2(matrix_1);
    }

    std::vector<std::vector<T>> InverseMatrix2() {
        return Inverse2x2(matrix_2);
    }

    // Print
    void PrintMatrix(const std::vector<std::vector<T>>& matrix) const {
        if (matrix.empty()) {
            std::cout << "(empty matrix)\n";
            return;
        }
        for (const auto& row : matrix) {
            for (const auto& val : row)
                std::cout << val << " ";
            std::cout << '\n';
        }
    }

private:
    bool SameSize() const {
        if (matrix_1.size() != matrix_2.size() || matrix_1[0].size() != matrix_2[0].size()) {
            PrintMismatch("add/subtract", matrix_1, matrix_2);
            return false;
        }
        return true;
    }

    void PrintMismatch(const std::string& op, const std::vector<std::vector<T>>& m1, const std::vector<std::vector<T>>& m2) const {
        std::cerr << "Error: Cannot " << op << " matrices.\n";
        std::cerr << "Matrix 1 size: " << m1.size() << "x" << (m1.empty() ? 0 : m1[0].size())
                  << ", Matrix 2 size: " << m2.size() << "x" << (m2.empty() ? 0 : m2[0].size()) << std::endl;
    }

    std::vector<std::vector<T>> Transpose(const std::vector<std::vector<T>>& matrix) {
        if (matrix.empty()) return {};
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        std::vector<std::vector<T>> result(cols, std::vector<T>(rows));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[j][i] = matrix[i][j];
        return result;
    }

    std::vector<std::vector<T>> ScalarMultiply(const std::vector<std::vector<T>>& matrix, T scalar) {
        if (matrix.empty()) return {};
        std::vector<std::vector<T>> result(matrix.size(), std::vector<T>(matrix[0].size()));
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix[0].size(); ++j)
                result[i][j] = matrix[i][j] * scalar;
        return result;
    }

    T Determinant2x2(const std::vector<std::vector<T>>& matrix) {
        if (matrix.size() != 2 || matrix[0].size() != 2) {
            std::cerr << "Error: Determinant is only implemented for 2x2 matrices.\n";
            return T();
        }
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    std::vector<std::vector<T>> Inverse2x2(const std::vector<std::vector<T>>& matrix) {
        if (matrix.size() != 2 || matrix[0].size() != 2) {
            std::cerr << "Error: Inverse is only implemented for 2x2 matrices.\n";
            return {};
        }
        T det = Determinant2x2(matrix);
        if (det == 0) {
            std::cerr << "Error: Cannot compute inverse. Determinant is zero.\n";
            return {};
        }
        std::vector<std::vector<T>> inverse(2, std::vector<T>(2));
        inverse[0][0] =  matrix[1][1] / det;
        inverse[0][1] = -matrix[0][1] / det;
        inverse[1][0] = -matrix[1][0] / det;
        inverse[1][1] =  matrix[0][0] / det;
        return inverse;
    }
};

