#pragma once

#include <cmath>
#include "BA/Utilities/Vector2.hpp"
#include "BA/Types.hpp"

namespace ba {

template<typename T>
class Circle {
public:
	Vector2<T> 		origin{};
	T 				radius{};

	constexpr Circle();
	constexpr Circle(Vector2<T> o, T r);
	template<typename U>
	constexpr Circle(const Circle<U>& other);

	constexpr double getArea() const;
	constexpr double circumference() const;

	constexpr bool intersects(const Circle& other) const;

}; // class Circle

using IntCircle = Circle<int>;
using FloatCircle = Circle<float>;

/********************************************
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Circle<T>.
*********************************************/
template <typename T>
constexpr Circle<T>::Circle() = default;

template <typename T>
constexpr Circle<T>::Circle(Vector2<T> o, T r) :
	origin(o),
	radius(r)
{

}

template <typename T>
template <typename U>
constexpr Circle<T>::Circle(const Circle<U>& other) :
	origin(other.origin),
	radius(static_cast<T>(other.radius))
{

}

template <typename T>
constexpr double Circle<T>::getArea() const {
	return PI * (radius * radius);
}

template <typename T>
constexpr double Circle<T>::circumference() const {
	return 2 * radius * PI;
}

template <typename T>
constexpr bool Circle<T>::intersects(const Circle<T>& other) const {
	return origin.distance(other.origin) <= (this->radius + other.radius);
}

} // namespace ba
