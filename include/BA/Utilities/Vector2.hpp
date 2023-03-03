#pragma once

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
	constexpr explicit Vector2(const Vector2<U>& other);

	constexpr SDL_Point toSDL_Point() const;

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
constexpr Vector2<T> operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T>
constexpr Vector2<T> operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

/***********************************
 * IMPLEMENTATIONS
***********************************/
#include <BA/Utilities/Vector2.inl>


// Define common types
using Vector2i = 	Vector2<int>;
using Vector2f = 	Vector2<float>;
using Vector2u = 	Vector2<unsigned int>;
using Vector2d =	Vector2<double>;
} // namespace ba