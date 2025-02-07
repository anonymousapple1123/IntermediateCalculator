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

int main() { //function calling
    const int rows = 3, cols = 3;
    vector<vector<int>> matrix1(rows, vector<int>(cols));
    vector<vector<int>> matrix2(rows, vector<int>(cols));
    vector<vector<int>> result(rows, vector<int>(cols));
    int choice;

    // Choose an operation 
    cout << "Choose an operation:\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Transpose of first matrix\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Input only necessary matrices
    if (choice >= 1 && choice <= 3) {
        cout << "Enter values for the first " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Enter value for matrix1[" << i << "][" << j << "]: ";
                cin >> matrix1[i][j];
            }
        }

        cout << "Enter values for the second " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Enter value for matrix2[" << i << "][" << j << "]: ";
                cin >> matrix2[i][j];
            }
        }
    } 
    else if (choice == 4) {
        cout << "Enter values for the " << rows << "x" << cols << " matrix to transpose:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Enter value for matrix1[" << i << "][" << j << "]: ";
                cin >> matrix1[i][j];
            }
        }
    } 
    else {
        cout << "Invalid choice!";
        return 1;
    }

    // Perform the chosen operation
    switch (choice) {
        case 1:
            addMatrices(rows, cols, matrix1, matrix2, result);
            cout << "Sum of the matrices:\n";
            break;
        case 2:
            subtractMatrices(rows, cols, matrix1, matrix2, result);
            cout << "Difference of the matrices:\n";
            break;
        case 3:
            multiplyMatrices(rows, cols, matrix1, matrix2, result);
            cout << "Product of the matrices:\n";
            break;
        case 4:
            result = vector<vector<int>>(cols, vector<int>(rows)); // Resize for transpose
            transposeMatrix(rows, cols, matrix1, result);
            cout << "Transpose of the matrix:\n";
            break;
    }

    // Output the result
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

