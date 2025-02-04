#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector> // Include this for std::remove

int parse_values() {
    std::string input;
    double a, b;

    // Prompt the user for input
    std::cout << "Enter a complex number in the format a + ib: ";
    std::getline(std::cin, input);

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
        return 1;
    }

    // Output the results
    std::cout << "Real part (a): " << a << std::endl;
    std::cout << "Imaginary part (b): " << b << std::endl;

    return 0;
}
