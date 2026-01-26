#pragma once

using namespace math
{
    template <typename T>
    Vector4D<T>::Vector4D()
    {
    }

    template <typename T>
    Vector4D<T>::Vector4D(T v1, T v2, T v3)
    {
    }

    template <typename T>
    T& Vector4D<T>::operator[](int i)
    {
    }

    template <typename T>
    const T& Vector4D<T>::operator[](int i) const
    {
    }

    template <typename T>
    Vector4D<T> Vector4D<T>::operator+(const Vector4D& other) const
    {
    }

    template <typename T>
    Vector4D<T>& Vector4D<T>::operator+=(const Vector4D& other)
    {
    }

    template <typename T>
    Vector4D<T> Vector4D<T>::operator-(const Vector4D& other) const
    {
    }

    template <typename T>
    Vector4D<T>& Vector4D<T>::operator-=(const Vector4D& other)
    {
    }

    template <typename T>
    template <typename M>
    Vector4D<T> Vector4D<T>::operator*(const M& scalar) const
    {
    }

    template <typename T>
    template <typename M>
    Vector4D<T>& Vector4D<T>::operator*=(const M& scalar)
    {
    }

    template <typename T>
    template <typename M>
    Vector4D<T> Vector4D<T>::operator/(const M& scalar) const
    {
    }

    template <typename T>
    template <typename M>
    Vector4D<T>& Vector4D<T>::operator/=(const M& scalar)
    {
    }

    template <typename T>
    T Vector4D<T>::dot(const Vector4D& other) const
    {
    }

    template <typename T>
    Vector4D<T> Vector4D<T>::cross(const Vector4D& other) const
    {
    }

    template <typename T>
    T Vector4D<T>::mag() const
    {
    }

    template <typename T>
    Vector4D<T> Vector4D<T>::normalize() const
    {
    }

    template <typename T>
    T Vector4D<T>::dot(const Vector4D& vecA, const Vector4D& vecB)
    {
    }

    template <typename T>
    Vector4D<T> Vector4D<T>::cross(const Vector4D& vecA, const Vector4D& vecB)
    {
    }

}