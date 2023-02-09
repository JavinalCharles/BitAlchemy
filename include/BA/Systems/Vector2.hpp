#pragma once

namespace ba {

template <typename T>
class Vector2 {
public: // Attributes
	T x;
	T y;

public: // Constructors
	Vector2(T X, T Y);
	Vector2();
	template <typename U>
	explicit Vector2(const Vector2<U>& other);

};

// OPERATORS
template<typename T>
Vector2<T> operator-(const Vector2<T>& right);

template<typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T>& operator*=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T>& operator/=(Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator*(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

/***********************************
 * IMPLEMENTATIONS
***********************************/


template<typename T>
Vector2<T>::Vector2(T X, T Y)
	: x(X), y(Y)
{

}

template<typename T>
Vector2<T>::Vector2()
	: x(), y() {

}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& other) 
	: x(other.x), y(other.y) {

}

/************************************
 * Vector2 OPERATORS
************************************/
template<typename T>
Vector2<T> operator-(const Vector2<T>& rhs) {
	return Vector2<T>(-rhs.x, -rhs.y);
}

template<typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

template<typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

template<typename T>
Vector2<T>& operator*=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	return lhs;
}

template<typename T>
Vector2<T>& operator/=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;
	return lhs;
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template<typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return lhs.x != rhs.x || lhs.y != rhs.y;
}

// Define common types
using Vector2i = 	Vector2<int>;
using Vector2f = 	Vector2<float>;
using Vector2u = 	Vector2<unsigned int>;
using Vector2d =		Vector2<double>;
} // namespace ba