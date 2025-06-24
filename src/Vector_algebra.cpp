#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>
#include <limits>
#include <utility>

template<typename T>
class Vector {
    static_assert(std::is_floating_point<T>::value, "Vector only supports floating-point types.");

private:
    std::vector<T> data;

public:
    // Constructor
    Vector(const std::vector<T>& input) : data(input) {}

    // Access data
    const std::vector<T>& GetData() const {
        return data;
    }

    // Size
    size_t Size() const {
        return data.size();
    }

    // Print vector
    void Print() const {
        if (data.empty()) {
            std::cout << "(empty vector)\n";
            return;
        }
        std::cout << "(";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i != data.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
    }

    // Scalar multiplication
    Vector<T> MultiplyByScalar(T scalar) const {
        std::vector<T> result = data;
        for (auto& val : result) val *= scalar;
        return Vector<T>(result);
    }

    // Magnitude
    T Magnitude() const {
        T sum = 0;
        for (const auto& val : data)
            sum += val * val;
        return std::sqrt(sum);
    }

    // Normalize
    Vector<T> Normalize() const {
        T mag = Magnitude();
        if (mag == 0) {
            std::cerr << "Error: Cannot normalize zero vector.\n";
            return Vector<T>({});
        }
        return MultiplyByScalar(1.0 / mag);
    }

    // Static: Add two vectors
    static Vector<T> Add(const Vector<T>& a, const Vector<T>& b) {
        if (a.Size() != b.Size()) {
            std::cerr << "Error: Cannot add vectors of different sizes.\n";
            return Vector<T>({});
        }
        std::vector<T> result(a.Size());
        for (size_t i = 0; i < a.Size(); ++i)
            result[i] = a.data[i] + b.data[i];
        return Vector<T>(result);
    }

    // Static: Subtract two vectors
    static Vector<T> Subtract(const Vector<T>& a, const Vector<T>& b) {
        if (a.Size() != b.Size()) {
            std::cerr << "Error: Cannot subtract vectors of different sizes.\n";
            return Vector<T>({});
        }
        std::vector<T> result(a.Size());
        for (size_t i = 0; i < a.Size(); ++i)
            result[i] = a.data[i] - b.data[i];
        return Vector<T>(result);
    }

    // Static: Dot product
    static T Dot(const Vector<T>& a, const Vector<T>& b) {
        if (a.Size() != b.Size()) {
            std::cerr << "Error: Cannot compute dot product on vectors of different sizes.\n";
            return T();
        }
        T result = 0;
        for (size_t i = 0; i < a.Size(); ++i)
            result += a.data[i] * b.data[i];
        return result;
    }

    // Static: Cross product (3D only)
    static Vector<T> Cross(const Vector<T>& a, const Vector<T>& b) {
        if (a.Size() != 3 || b.Size() != 3) {
            std::cerr << "Error: Cross product is only defined for 3D vectors.\n";
            return Vector<T>({});
        }
        std::vector<T> result(3);
        result[0] = a.data[1] * b.data[2] - a.data[2] * b.data[1];
        result[1] = a.data[2] * b.data[0] - a.data[0] * b.data[2];
        result[2] = a.data[0] * b.data[1] - a.data[1] * b.data[0];
        return Vector<T>(result);
    }

    // Static: Angle between vectors in both radians and degrees
    static std::pair<T, T> AngleBetween(const Vector<T>& a, const Vector<T>& b) {
        if (a.Size() != b.Size()) {
            std::cerr << "Error: Cannot compute angle between vectors of different sizes.\n";
            return {std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN()};
        }

        T dot = Dot(a, b);
        T magA = a.Magnitude();
        T magB = b.Magnitude();

        if (magA == 0 || magB == 0) {
            std::cerr << "Error: Cannot compute angle with zero-length vector.\n";
            return {std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN()};
        }

        T cosTheta = dot / (magA * magB);
        cosTheta = std::min(T(1), std::max(T(-1), cosTheta));

        T radians = std::acos(cosTheta);
        T degrees = radians * (180.0 / M_PI);

        return {radians, degrees};
    }
};
