#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "matrices_operation.h"
#include "complex_number_arithmetics.h"

// Function to display options to the user
void displayChoices() {
    std::cout << "Choose an operation:\n";
    std::cout << "1. Complex Number Operations\n";
    std::cout << "2. Matrix Operations\n";
    std::cout << "Enter your choice: ";
}

// Parse a complex number string (e.g., "3+4i") into a vector of two elements: [real, imaginary]
std::vector<double> parse_complex(const std::string& complexStr) {
    std::vector<double> result(2, 0.0);
    std::regex complexPattern("([+-]?\\d*\\.?\\d+)([+-]?\\d*\\.?\\d*)i?");
    std::smatch match;

    if (std::regex_search(complexStr, match, complexPattern) && match.size() == 3) {
        result[0] = std::stod(match[1].str());  // Real part
        result[1] = std::stod(match[2].str());  // Imaginary part
    } else {
        std::cerr << "Invalid complex number format" << std::endl;
    }

    return result;
}

// Function for complex number operations
void complexOperations() {
    std::vector<double> result_vec;
    std::string number_1, number_2;

    std::cout << "Enter first complex number (e.g., 3+4i): ";
    std::getline(std::cin, number_1);

    std::cout << "Enter second complex number (e.g., 1-2i): ";
    std::getline(std::cin, number_2);

    std::vector<double> parsed_num1 = parse_complex(number_1);
    std::vector<double> parsed_num2 = parse_complex(number_2);

    if ((parsed_num1.size() == 2) && (parsed_num2.size() == 2)) {
        ComplexNumber<double> complex(parsed_num1[0], parsed_num1[1], parsed_num2[0], parsed_num2[1]);
        int choice;
        std::cout << "Choose operation:\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Modulus\n6. Conjugate\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To clear the newline character left by std::cin

        switch (choice) {
            case 1:
                result_vec = complex.AddComplexNumber();
                std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
                break;
            case 2:
                result_vec = complex.SubtractComplexNumber();
                std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
                break;
            case 3:
                result_vec = complex.MultiplyComplexNumber();
                std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
                break;
            case 4:
                result_vec = complex.DivideComplexNumber();
                std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
                break;
            case 5:
                result_vec = complex.ModulusComplexNumber();
                std::cout << "Modulus of first: " << result_vec[0] << ", Modulus of second: " << result_vec[1] << std::endl;
                break;
            case 6:
                result_vec = complex.ConjugateComplexNumber();
                std::cout << "Conjugate of first: " << result_vec[0] << " + " << result_vec[1] << "i\n";
                std::cout << "Conjugate of second: " << result_vec[2] << " + " << result_vec[3] << "i\n";
                break;
            default:
                std::cerr << "Invalid choice!" << std::endl;
                break;
        }
    } else {
        std::cerr << "Failed to parse complex numbers." << std::endl;
    }
}

// Function for matrix operations
void matrixOperations() {
    const int rows = 3, cols = 3;
    std::vector<std::vector<int>> matrix1(rows, std::vector<int>(cols));
    std::vector<std::vector<int>> matrix2(rows, std::vector<int>(cols));
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));
    int choice;

    // Choose an operation 
    std::cout << "Choose an operation:\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Transpose of first matrix\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Input only necessary matrices
    if (choice >= 1 && choice <= 3) {
        std::cout << "Enter values for the first " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Enter value for matrix1[" << i << "][" << j << "]: ";
                std::cin >> matrix1[i][j];
            }
        }

        std::cout << "Enter values for the second " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Enter value for matrix2[" << i << "][" << j << "]: ";
                std::cin >> matrix2[i][j];
            }
        }
    } 
    else if (choice == 4) {
        std::cout << "Enter values for the " << rows << "x" << cols << " matrix to transpose:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Enter value for matrix1[" << i << "][" << j << "]: ";
                std::cin >> matrix1[i][j];
            }
        }
    } 
    else {
        std::cout << "Invalid choice!";
        return;
    }

    // Perform the chosen operation
    switch (choice) {
        case 1:
            addMatrices(rows, cols, matrix1, matrix2, result);
            std::cout << "Sum of the matrices:\n";
            break;
        case 2:
            subtractMatrices(rows, cols, matrix1, matrix2, result);
            std::cout << "Difference of the matrices:\n";
            break;
        case 3:
            multiplyMatrices(rows, cols, matrix1, matrix2, result);
            std::cout << "Product of the matrices:\n";
            break;
        case 4:
            result = std::vector<std::vector<int>>(cols, std::vector<int>(rows)); // Resize for transpose
            transposeMatrix(rows, cols, matrix1, result);
            std::cout << "Transpose of the matrix:\n";
            break;
    }

    // Output the result
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int operationChoice;

    // Display choices for the user
    displayChoices();
    std::cin >> operationChoice;
    std::cin.ignore(); // To clear the newline character left by std::cin

    if (operationChoice == 1) {
        // Perform complex number operations
        complexOperations();
    } else if (operationChoice == 2) {
        // Perform matrix operations
        matrixOperations();
    } else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    return 0;
}
