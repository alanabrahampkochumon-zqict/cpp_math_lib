namespace math {

	template <typename T>
	Vector2D<T>::Vector2D(): x(T(0), y(T(0)) {}

	template <typename T>
	Vector2D<T>::Vector2D(T v1, T v2): x(v1), y(v2) {}

	template <typename T>
	T& Vector2D<T>::operator[](int i)
	{
		return &this[i];
	}

	template <typename T>
	const T& Vector2D<T>::operator[](int i) const
	{
		return &this[i];
	}

	template <typename T>
	Vector2D<T> Vector2D<T>::operator+(const Vector2D& other) const
	{
	}

	template <typename T>
	Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& other)
	{
	}

	template <typename T>
	Vector2D<T> Vector2D<T>::operator-(const Vector2D& other) const
	{
	}

	template <typename T>
	Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& other)
	{
	}

	template <typename T>
	template <typename M>
	Vector2D<T> Vector2D<T>::operator*(const M& scalar) const
	{
	}

	template <typename T>
	template <typename M>
	Vector2D<T>& Vector2D<T>::operator*=(const M& scalar)
	{
	}

	template <typename T>
	template <typename M>
	Vector2D<T> Vector2D<T>::operator/(const M& scalar) const
	{
	}

	template <typename T>
	template <typename M>
	Vector2D<T>& Vector2D<T>::operator/=(const M& scalar)
	{
	}

	template <typename T>
	T Vector2D<T>::dot(const Vector2D& other) const
	{
	}

	template <typename T>
	T Vector2D<T>::cross(const Vector2D& other) const
	{
	}

	template <typename T>
	T Vector2D<T>::mag() const
	{
	}

	template <typename T>
	Vector2D<T> Vector2D<T>::normalize() const
	{
	}

	template <typename T>
	T Vector2D<T>::dot(const Vector2D& vecA, const Vector2D& vecB)
	{
	}

	template <typename T>
	T Vector2D<T>::cross(const Vector2D& vecA, const Vector2D& vecB)
	{
	}


	template<typename T, typename M>
	Vector2D<T> operator*(M scalar, const Vector2D<T>& vector)
	{

	}
}