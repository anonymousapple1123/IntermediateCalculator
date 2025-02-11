#include <iostream>
#include <vector>
using namespace std;

// Function to perform addition of matrices
void addMatrices(int rows, int cols, const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& sum) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Function to perform subtraction of matrices
void subtractMatrices(int rows, int cols, const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& diff) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            diff[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

// Function to perform multiplication of matrices
void multiplyMatrices(int rows, int cols, const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& product) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            product[i][j] = 0; // Initialize the element
            for (int k = 0; k < cols; k++) { // Perform multiplication and summing of products
                product[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Function to perform transpose of a matrix
void transposeMatrix(int rows, int cols, const vector<vector<int>>& matrix, vector<vector<int>>& transpose) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j]; // Swap rows with columns
        }
    }
}


