#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "vector_algebra.hpp"

template<typename T>
Vector<T>::Vector(const std::vector<T>& input) : data(input) {}

template<typename T>
const std::vector<T>& Vector<T>::GetData() const {
    return data;
}

template<typename T>
size_t Vector<T>::Size() const {
    return data.size();
}

template<typename T>
void Vector<T>::Print() const {
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

template<typename T>
Vector<T> Vector<T>::MultiplyByScalar(T scalar) const {
    std::vector<T> result = data;
    for (auto& val : result) val *= scalar;
    return Vector<T>(result);
}

template<typename T>
T Vector<T>::Magnitude() const {
    T sum = 0;
    for (const auto& val : data)
        sum += val * val;
    return std::sqrt(sum);
}

template<typename T>
Vector<T> Vector<T>::Normalize() const {
    T mag = Magnitude();
    if (mag == 0) {
        std::cerr << "Error: Cannot normalize zero vector.\n";
        return Vector<T>({});
    }
    return MultiplyByScalar(1.0 / mag);
}

template<typename T>
Vector<T> Vector<T>::Add(const Vector<T>& a, const Vector<T>& b) {
    if (a.Size() != b.Size()) {
        std::cerr << "Error: Cannot add vectors of different sizes.\n";
        return Vector<T>({});
    }
    std::vector<T> result(a.Size());
    for (size_t i = 0; i < a.Size(); ++i)
        result[i] = a.data[i] + b.data[i];
    return Vector<T>(result);
}

template<typename T>
Vector<T> Vector<T>::Subtract(const Vector<T>& a, const Vector<T>& b) {
    if (a.Size() != b.Size()) {
        std::cerr << "Error: Cannot subtract vectors of different sizes.\n";
        return Vector<T>({});
    }
    std::vector<T> result(a.Size());
    for (size_t i = 0; i < a.Size(); ++i)
        result[i] = a.data[i] - b.data[i];
    return Vector<T>(result);
}

template<typename T>
T Vector<T>::Dot(const Vector<T>& a, const Vector<T>& b) {
    if (a.Size() != b.Size()) {
        std::cerr << "Error: Cannot compute dot product on vectors of different sizes.\n";
        return T();
    }
    T result = 0;
    for (size_t i = 0; i < a.Size(); ++i)
        result += a.data[i] * b.data[i];
    return result;
}

template<typename T>
Vector<T> Vector<T>::Cross(const Vector<T>& a, const Vector<T>& b) {
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

template<typename T>
std::pair<T, T> Vector<T>::AngleBetween(const Vector<T>& a, const Vector<T>& b) {
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

// Explicit instantiations (optional)
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;

#endif // VECTOR_CPP
