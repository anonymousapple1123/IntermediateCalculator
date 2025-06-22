#include "matrices_operation.hpp"
#include <iostream>
#include <type_traits>
#include <vector>
#include <cmath>

using std::vector;
template<typename T>

vector<vector<T>> MatrixOperation<T>::operator+(const MatrixOperation<T>& matrix_2){
     if (!MatrixOperation::isequal(matrix_2)) return {};
        size_t rows = matrix.size(), cols = matrix[0].size();
        vector<vector<T>> result(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i){
            for (size_t j = 0; j < cols; ++j){
                result[i][j] = matrix[i][j] + matrix_2[i][j];
            }
        }
        return result;
}
template<typename  T>
vector<vector<T>> MatrixOperation<T>::operator-(const MatrixOperation<T>& matrix_2) {
        if (!MatrixOperation::isequal(matrix_2)) return {};
        size_t rows = matrix.size(), cols = matrix[0].size();
        vector<vector<T>> result(rows, vector<T>(cols));
        for (size_t i = 0; i < rows; ++i){
            for (size_t j = 0; j < cols; ++j){
                result[i][j] = matrix[i][j] - matrix_2[i][j];
            }
        }
        return result;
    }

template<typename T>
vector<vector<T>> MatrixOperation<T>::operator*(const MatrixOperation<T>& matrix_2) {
        if (matrix.empty() || matrix_2.empty() || matrix[0].size() != matrix_2.size()) {
           MatrixOperation::isequal_v(matrix_2);
            return {};
        }
        size_t rows = matrix.size();
        size_t cols = matrix_2[0].size();
        size_t common = matrix[0].size();

        std::vector<std::vector<T>> result(rows, std::vector<T>(cols, 0));
        for (size_t i = 0; i < rows; ++i){
            for (size_t j = 0; j < cols; ++j){
                for (size_t k = 0; k < common; ++k){
                    result[i][j] += matrix[i][k] * matrix_2[k][j];
                }
            }
        }
        return result;
    }

template<typename T>
void MatrixOperation<T>::PrintMatrix()const{
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

template<typename T>
bool MatrixOperation<T>::isequal(MatrixOperation<T>& matrix_2) const{
    if (matrix.size() != matrix_2.size() || matrix[0].size() != matrix_2[0].size()) {
            return false;
        }
        return true;
}
template<typename T>
void MatrixOperation<T>::isequal_v(const std::vector<std::vector<T>>& m2) const {
    std::cerr << "Matrix 1 size: " << matrix.size() << "x" << (matrix.empty() ? 0 : matrix[0].size())
                << ", Matrix 2 size: " << m2.size() << "x" << (m2.empty() ? 0 : m2[0].size()) << std::endl;
}
template<typename T>
vector<vector<T>> MatrixOperation<T>::Transpose(){
if (matrix.empty()) return {};
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        std::vector<std::vector<T>> result(cols, std::vector<T>(rows));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[j][i] = matrix[i][j];
        return result; 
}

template<typename T>
vector<vector<T>> MatrixOperation<T>::ScalarMultiply (T scalar){
if (matrix.empty()) return {};
        std::vector<std::vector<T>> result(matrix.size(), std::vector<T>(matrix[0].size()));
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix[0].size(); ++j)
                result[i][j] = matrix[i][j] * scalar;
        return result;   
}

template<typename T>
T MatrixOperation<T>::Determinant() {
        if (matrix.size() != 2 || matrix[0].size() != 2) {
            std::cerr << "Error: Determinant is only implemented for 2x2 matrices.\n";
            return T();
        }
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

template<typename T>
vector<vector<T>> MatrixOperation<T>::Inverse(){        
    if (matrix.size() != 2 || matrix[0].size() != 2) {
            std::cerr << "Error: Inverse is only implemented for 2x2 matrices.\n";
            return {};
        }
        T det = Determinant(matrix);
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