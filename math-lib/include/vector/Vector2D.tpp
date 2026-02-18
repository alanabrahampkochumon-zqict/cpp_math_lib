#pragma once

#include <type_traits>
#include "Vector2D.h"

namespace math {

    template <arithmetic T>
    Vector2D<T>::Vector2D(): x(T(0)), y(T(0)) { }

    template <arithmetic T>
    Vector2D<T>::Vector2D(T v1, T v2): x(v1), y(v2) { }

    template <arithmetic T>
    template <arithmetic U>
    Vector2D<T>::Vector2D(const Vector2D<U>& other):
    x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
	{ }

    template <arithmetic T>
    T& Vector2D<T>::operator[](std::size_t i)
    {
        return (&x)[i];
    }

    template <arithmetic T>
    const T& Vector2D<T>::operator[](std::size_t i) const
    {
        return (&x)[i];
    }

    template <arithmetic T>
    template <arithmetic S>
    auto Vector2D<T>::operator+(const Vector2D<S>& other) const -> Vector2D<std::common_type_t<S, T>>
    {
        using R = std::common_type_t<T, S>;
        return Vector2D<R>(x + other.x, y + other.y);
    }

    template <arithmetic T>
    template <arithmetic U>
    Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<U>& other)
    {
        x += static_cast<T>(other.x);
        y += static_cast<T>(other.y);
        return *this;
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::operator-(const Vector2D<U>& other) const -> Vector2D<std::common_type_t<T, U>>
    {
        using R = std::common_type_t<T, U>;
        return Vector2D<R>(x - other.x, y - other.y);
    }

    template <arithmetic T>
    template <arithmetic U>
    Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<U>& other)
    {
        x -= static_cast<T>(other.x);
        y -= static_cast<T>(other.y);
        return *this;
    }

    template <arithmetic T>
    template <arithmetic S>
    auto Vector2D<T>::operator*(S scalar) const -> Vector2D<std::common_type_t<T, S>>
    {
        using R = std::common_type_t<T, S>;
        return Vector2D<R>(x * scalar, y * scalar);
    }

    template <arithmetic T, arithmetic S>
    auto operator*(S scalar, const Vector2D<T>& vector) -> Vector2D<std::common_type_t<S, T>>
    {
        return vector * scalar;
    }

    template <arithmetic T>
    template <arithmetic S>
    Vector2D<T>& Vector2D<T>::operator*=(S scalar)
    {
        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        return *this;
    }

    template <arithmetic T>
    template <arithmetic S>
    auto Vector2D<T>::operator/(S scalar) const -> Vector2D<std::common_type_t<T, S>>
    {
        using R = std::common_type_t<T, S>;
        R factor = R(1) / static_cast<R>(scalar);
        return Vector2D<R>(x * factor, y * factor);
    }

    template <arithmetic T>
    template <arithmetic S>
    Vector2D<T>& Vector2D<T>::operator/=(S scalar)
    {
        using R = std::common_type_t<T, S>;
        R factor = R(1) / static_cast<R>(scalar);
        x = static_cast<T>(factor * x);
        y = static_cast<T>(factor * y);
        return *this;
    }

    template <arithmetic T>
    template <arithmetic S>
    auto Vector2D<T>::dot(const Vector2D<S>& other) const -> std::common_type_t<T, S>
    {
        return x * other.x + y * other.y;
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::dot(const Vector2D& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>
    {
        return vectorA.dot(vectorB);
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::cross(const Vector2D<U>& other) const -> std::common_type_t<T, U>
    {
        return x * other.y - y * other.x;
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::cross(const Vector2D<T>& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>
    {
        return vectorA.cross(vectorB);
    }
        
    template <arithmetic T>
    T Vector2D<T>::mag() const
    {
        return sqrt(x * x + y * y);
    }

    template <arithmetic T>
    Vector2D<T> Vector2D<T>::normalize() const
    {
        return (*this) / this->mag();
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::project(const Vector2D<U>& onto, bool ontoNormalized) const -> Vector2D<std::common_type_t<T, U>>
    {
        if (ontoNormalized)
        {
            // Pb||a^ = dot(a, b) * b;
            return this->dot(onto) * onto;
        }
        else
        {
            // Pb||a = dot(a, b)/dot(b,b) * b;
            return this->dot(onto) / onto.dot(onto) * onto;
        }
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::project(const Vector2D& vector, const Vector2D<U>& onto, bool ontoNormalized) -> Vector2D<std::common_type_t<T, U>>
    {
        return vector.project(onto, ontoNormalized);
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::reject(const Vector2D<U>& onto, bool ontoNormalized) const -> Vector2D<std::common_type_t<T, U>>
    {
        return *this - this->project(onto, ontoNormalized);
    }

    template <arithmetic T>
    template <arithmetic U>
    auto Vector2D<T>::reject(const Vector2D& vector, const Vector2D<U>& onto,
	    bool ontoNormalized) -> Vector2D<std::common_type_t<T, U>>
    {
        return vector.reject(onto, ontoNormalized);
    }
}