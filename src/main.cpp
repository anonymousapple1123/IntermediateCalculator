#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include "complex_number_arithmetics.h"

std::vector<double> parse_complex(std::string input) {
    double a, b;
    // Remove spaces from the input
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // Find the position of the '+' or '-' sign for the imaginary part
    size_t plusPos = input.find('+');
    size_t minusPos = input.find('-');

    // Determine the position of the imaginary part
    size_t signPos = (plusPos != std::string::npos) ? plusPos : minusPos;

    if (signPos != std::string::npos) {
        // Extract the real part (a)
        std::string realPart = input.substr(0, signPos);
        a = std::stod(realPart);

        // Extract the imaginary part (b)
        std::string imaginaryPart = input.substr(signPos);
        // Remove the 'i' character
        imaginaryPart.erase(std::remove(imaginaryPart.begin(), imaginaryPart.end(), 'i'), imaginaryPart.end());
        b = std::stod(imaginaryPart);
    } else {
        std::cerr << "Invalid input format." << std::endl;
        return {-1,-1} ;
    }

    std::vector<double> result;
    result.push_back(a);
    result.push_back(b);
    // std::cout << "Real part (a): " << a << std::endl;
    // std::cout << "Imaginary part (b): " << b << std::endl;

    return result;
}

void displayChoices(){
    
    return;
}
int main() {
    std::vector<double> result_vec;
    std::string number_1, number_2;

    std::cout << "Enter first number : ";
    if (!(std::getline(std::cin, number_1))) {
        std::cerr << "Failed to read input." << std::endl;
        return 1;
    }

    std::cout << "Enter second number : ";
    if (!(std::getline(std::cin, number_2))) {
        std::cerr << "Failed to read input." << std::endl;
        return 1;
    }

    std::vector<double> parsed_num1 = parse_complex(number_1);
    std::vector<double> parsed_num2 = parse_complex(number_2);

    if ((parsed_num1.size() == 2) && (parsed_num2.size() == 2)) {
        ComplexNumber<double> complex(parsed_num1[0], parsed_num1[1], parsed_num2[0], parsed_num2[1]);
        int choice = 1;
        switch (choice) {
        case 1:
            result_vec = complex.AddComplexNumber();
            std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
            break;
        default:
            break;
        }
    } else {
        std::cerr << "Failed to parse complex numbers." << std::endl;
    }

    return 0;
}
