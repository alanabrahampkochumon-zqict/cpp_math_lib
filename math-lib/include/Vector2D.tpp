#pragma once

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
    template <typename M>
    Vector2D<T> Vector2D<T>::operator*(const M& scalar) const
    {
        return Vector2D(x * scalar, y * scalar);
    }

    template <typename T>
    template <typename M>
    Vector2D<T>& Vector2D<T>::operator*=(const M& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <typename T>
    template <typename M>
    Vector2D<T> Vector2D<T>::operator/(const M& scalar) const
    {
        T factor = T(1) / scalar;
        return Vector2D(x * factor, y * factor);
    }

    template <typename T>
    template <typename M>
    Vector2D<T>& Vector2D<T>::operator/=(const M& scalar)
    {
        T factor = T(1) / scalar;
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

    template<typename T, typename M>
    Vector2D<T> operator*(M scalar, const Vector2D<T>& vector)
    {
        return vector * scalar;
    }

}