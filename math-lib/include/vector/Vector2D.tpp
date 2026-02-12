#pragma once

#include <type_traits>
#include "Vector2D.h"

namespace math {

    template <typename T>
    Vector2D<T>::Vector2D(): x(T(0)), y(T(0)) { }

    template <typename T>
    Vector2D<T>::Vector2D(T v1, T v2): x(v1), y(v2) { }

    template <typename T>
    T& Vector2D<T>::operator[](int i)
    {
        return ( &x)[i];
    }

    template <typename T>
    const T& Vector2D<T>::operator[](int i) const
    {
        return (&x)[i];
    }

    template <typename T>
    Vector2D<T> Vector2D<T>::operator+(const Vector2D& other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    template <typename T>
    Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    template <typename T>
    Vector2D<T> Vector2D<T>::operator-(const Vector2D& other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    template <typename T>
    Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template <typename T>
    template <typename S, typename>
    Vector2D<T> Vector2D<T>::operator*(const S& scalar) const
    {
        static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
        return Vector2D(x * scalar, y * scalar);
    }

    template <typename T>
    template <typename S, typename>
    Vector2D<T>& Vector2D<T>::operator*=(const S& scalar)
    {
        static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
        x *= static_cast<T>(scalar);
        y *= static_cast<T>(scalar);
        return *this;
    }

    template <typename T>
    template <typename S>
    Vector2D<T> Vector2D<T>::operator/(const S& scalar) const
    {
        static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
        T factor = T(1) / static_cast<T>(scalar);
        return Vector2D(x * factor, y * factor);
    }

    template<typename T>
    template<typename S>
    Vector2D<T> Vector2D<T>::project(const Vector2D<S>& onto, bool ontoNormalized) const
    {
        if (ontoNormalized)
        {
            // Pb||a^ = dot(a, b) * b;
            return this->dot(onto) * onto;
        }
    	else
        {
            // Pb||a = dot(a, b)/dot(b,b) * b;
            return this->dot(onto) / Vector2D<T>::dot(onto, onto) * onto;
        }
        
    }

    template <typename T>
    template <typename S>
    Vector2D<T> Vector2D<T>::reject(const Vector2D<S>& onto, bool ontoNormalized) const
    {
        return *this - this->project(onto, ontoNormalized);
    }

    template <typename T>
    template <typename S>
    Vector2D<T>& Vector2D<T>::operator/=(const S& scalar)
    {
        static_assert(std::is_arithmetic_v<S>, "scalar must be an integral or float(int, float, double, etc.)");
        T factor = T(1) / static_cast<T>(scalar);
        x *= factor;
        y *= factor;
        return *this;
    }

    template <typename T>
    T Vector2D<T>::dot(const Vector2D& other) const
    {
        return x * other.x + y * other.y;
    }

    template <typename T>
    T Vector2D<T>::cross(const Vector2D& other) const
    {
        return x * other.y - y * other.x;
    }

    template <typename T>
    T Vector2D<T>::mag() const
    {
        return sqrt(x * x + y * y);
    }

    template <typename T>
    Vector2D<T> Vector2D<T>::normalize() const
    {
        return (*this) / this->mag();
    }

    template <typename T>
    T Vector2D<T>::dot(const Vector2D& vecA, const Vector2D& vecB)
    {
        return vecA.dot(vecB);
    }

    template <typename T>
    T Vector2D<T>::cross(const Vector2D& vecA, const Vector2D& vecB)
    {
        return vecA.cross(vecB);
    }

    template <typename T>
    template <typename S>
    Vector2D<T> Vector2D<T>::project(const Vector2D& vector, const Vector2D<S>& onto, bool ontoNormalized)
    {
        return vector.project(onto, ontoNormalized);
    }

    template <typename T>
    template <typename S>
    Vector2D<T> Vector2D<T>::reject(const Vector2D& vector, const Vector2D<S>& onto, bool ontoNormalized)
    {
        return vector - vector.project(onto, ontoNormalized);
    }

    template<typename T, typename M>
    Vector2D<T> operator*(M scalar, const Vector2D<T>& vector)
    {
        static_assert(std::is_arithmetic_v<M>, "scalar must be an integral or float(int, float, double, etc.)");
        return vector * scalar;
    }

}