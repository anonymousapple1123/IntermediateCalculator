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
    Vector(const std::vector<T>& input);

    const std::vector<T>& GetData() const;
    size_t Size() const;
    void Print() const;

    Vector<T> MultiplyByScalar(T scalar) const;
    T Magnitude() const;
    Vector<T> Normalize() const;

    static Vector<T> Add(const Vector<T>& a, const Vector<T>& b);
    static Vector<T> Subtract(const Vector<T>& a, const Vector<T>& b);
    static T Dot(const Vector<T>& a, const Vector<T>& b);
    static Vector<T> Cross(const Vector<T>& a, const Vector<T>& b);
    static std::pair<T, T> AngleBetween(const Vector<T>& a, const Vector<T>& b);
};

//#include "vector_algebra.cpp"  // Include the .cpp for template definitions if not instantiating explicitly
