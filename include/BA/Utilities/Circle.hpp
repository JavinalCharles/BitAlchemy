#pragma once

#include <cmath>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

const double Pi = 3.14159265359;

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

	bool intersects(const Circle& other) const;
	
}; // class Circle


#include <BA/Utilities/Circle.inl>

using IntCircle = Circle<int>;
using FloatCircle = Circle<float>



} // namespace ba