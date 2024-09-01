#pragma once

#include <cmath>
#include <SDL2/SDL.h>

namespace ba {

template <typename T>
class Vector2 {
public: // Attributes
	T x{};
	T y{};

public: // Constructors
	constexpr Vector2(T X, T Y);
	constexpr Vector2();
	template <typename U>
	constexpr Vector2(const Vector2<U>& other);

	constexpr SDL_Point toSDL_Point() const;

	constexpr float distance(const Vector2<T>& other) const;

}; // class Vector2

// OPERATORS
template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T> operator*(const Vector2<T>& lhs, T rhs);

template <typename T>
constexpr Vector2<T> operator*(T lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& lhs, T rhs);

template <typename T>
constexpr Vector2<T> operator/(const Vector2<T>& lhs, T rhs);

template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& lhs, T rhs);

template <typename T>
constexpr bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr float distance(const Vector2<T>& lhs, const Vector2<T>& rhs);

// Define common types
using Vector2i = 	Vector2<int>;
using Vector2f = 	Vector2<float>;
using Vector2u = 	Vector2<unsigned int>;
using Vector2d =	Vector2<double>;

/**
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Vector2<T>
**/
template <typename T>
constexpr Vector2<T>::Vector2() = default;

template<typename T>
constexpr Vector2<T>::Vector2(T X, T Y) :
	x(X),
	y(Y)
{

}

template <typename T>
template <typename U>
constexpr Vector2<T>::Vector2(const Vector2<U>& other)  :
	x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y))
{

}

template <typename T>
constexpr SDL_Point Vector2<T>::toSDL_Point() const {
	return SDL_Point{
		static_cast<int>(x),
		static_cast<int>(y)
	};
}

template <typename T>
constexpr float Vector2<T>::distance(const Vector2<T>& other) const {
	return static_cast<float>(std::sqrt(std::exp2(other.x - this->x) + std::exp2(other.y - this->y)));
}


/**
 * Vector2 OPERATORS
**/
template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& rhs) {
	return Vector2<T>(-rhs.x, -rhs.y);
}

template<typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

template<typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

template<typename T>
constexpr Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template<typename T>
constexpr Vector2<T> operator*(const Vector2<T>& lhs, T rhs) {
	return Vector2<T>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T>
constexpr Vector2<T> operator*(T lhs, const Vector2<T>& rhs) {
	return Vector2<T>(rhs.x * lhs, rhs.y * lhs);
}

template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& lhs, T rhs) {
	lhs.x *= rhs;
	lhs.y *= rhs;

	return lhs;
}

template<typename T>
constexpr Vector2<T> operator/(const Vector2<T>& lhs, T rhs) {
	return Vector2<T>(lhs.x / rhs, lhs.y / rhs);
}

template <typename T>
constexpr Vector2<T> operator/=(Vector2<T>& lhs, T rhs) {
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

template<typename T>
constexpr bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T>
constexpr bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return lhs.x != rhs.x || lhs.y != rhs.y;
}

template <typename T>
constexpr float distance(const Vector2<T>& lhs, const Vector2<T>& rhs) {
	return static_cast<float>(std::sqrt(
		std::exp2(rhs.x - lhs.x) + std::exp2(rhs.y - lhs.y)
	));
}



} // namespace ba
