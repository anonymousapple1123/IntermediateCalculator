#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <cmath>

template<typename T, typename Enable = void>
class ComplexNumber;

template<typename T>
class ComplexNumber<T, typename std::enable_if<std::is_floating_point<T>::value && std::is_signed<T>::value>::type> {
private:
    T real_1;
    T real_2;
    T imaginary_1;
    T imaginary_2;

public:
    ComplexNumber(T real_1, T imaginary_1, T real_2, T imaginary_2)
        : real_1(real_1), imaginary_1(imaginary_1), real_2(real_2), imaginary_2(imaginary_2) {}

    std::vector<T> AddComplexNumber() {
        std::vector<T> result;
        result.push_back(real_1 + real_2);
        result.push_back(imaginary_1 + imaginary_2);
        return result;
    }

    std::vector<T> SubtractComplexNumber() {
        std::vector<T> result;
        result.push_back(real_1 - real_2);
        result.push_back(imaginary_1 - imaginary_2);
        return result;
    }
    std::vector<T> MultiplyComplexNumber(){
        std::vector<T> result;
        result.push_back(real_1 * real_2 - imaginary_1 * imaginary_2);
        result.push_back(real_1 * imaginary_2 + real_2 * imaginary_1);
        return result;
    }
    std::vector<T> DivideComplexNumber(){
    std::vector<T> result;
    T denominator = real_2 * real_2 + imaginary_2 * imaginary_2;
    if (denominator == 0) {
        std::cerr << "Error: Division by zero is not allowed." << std::endl;
        return result;
    }
    T real_part = (real_1 * real_2 + imaginary_1 * imaginary_2) / denominator;
    T imaginary_part = (imaginary_1 * real_2 - real_1 * imaginary_2) / denominator;
    result.push_back(real_part);
    result.push_back(imaginary_part);
    return result;
    }

    std::vector<T> PowerOfI(int exponent){
        std::vector<T> result;
         if (!std::is_integral<decltype(exponent)>::value) {
        std::cerr << "Error: Exponent must be an integer." << std::endl;
        return result;
        }
        if (exponent < 0) {
        std::cerr << "Error: Negative exponents are not supported for PowerOfI." << std::endl;
        return result;
        }
        int cycle = exponent % 4;
        if (cycle == 0) result.push_back(static_cast<T>(1));
        else if (cycle == 1) {
        result.push_back(static_cast<T>(0));
        result.push_back(static_cast<T>(1));
        }
        else if (cycle == 2) result.push_back(static_cast<T>(-1));
        else {
        result.push_back(static_cast<T>(0));
        result.push_back(static_cast<T>(-1));
        }
        return result;
     /*
        std::is_integral<T> is a C++ type trait that checks if T is an integer type.
        decltype(exponent) ensures that we check the actual data type of exponent.
        If exponent is not an integer, std::is_integral returns false.
     */
    }
    
std::vector<T>ConjugateComplexNumber() {
    std::vector<T> result;
    result.push_back(real_1);
    result.push_back(-imaginary_1);
    result.push_back(real_2);
    result.push_back(-imaginary_2);
    return result;
}

std::vector<T>ModulusComplexNumber() {
    std::vector<T> result;
    result.push_back(std::sqrt(real_1 * real_1 + imaginary_1 * imaginary_1));
    result.push_back(std::sqrt(real_2 * real_2 + imaginary_2 * imaginary_2));
    return result;
}
};

#endif // COMPLEXNUMBER_H