#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "complex_number_arithmetics.h"

inline std::vector<double> parse_complex(const std::string& complex_str) {
    std::string command = "complex_parser.exe \"" + complex_str + "\"";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to open pipe to executable." << std::endl;
        return {};
    }
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    int status = pclose(pipe);
    if (status != 0) {
        std::cerr << "Executable returned an error." << std::endl;
        return {};
    }
    double a, b;
    if (sscanf(result.c_str(), "%lf,%lf", &a, &b) == 2) {
        return {a, b};
    } else {
        std::cerr << "Failed to parse output from executable." << std::endl;
        return {};
    }
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
        int choice = 2;
        switch (choice) {
        case 1:
            result_vec = complex.AddComplexNumber();
            std::cout << "= " << result_vec[0] << " + " << result_vec[1] << "i" << std::endl;
            break;
        case 2:
            result_vec=complex.MultiplyComplexNumber();
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
