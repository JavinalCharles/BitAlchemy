#pragma once

#include "BA/Utilities/Vector2.hpp"

namespace ba {

template<typename T>
class Line {
public:
	constexpr Line();
	constexpr Line(const Vector2<T>& _p1, const Vector2<T>& _p2);
	constexpr Line(T x1, T y1, T x2, T y2);

	template <typename U>
	constexpr Line(const Line<U>& otherLine);

public:
	constexpr float length() const;
	/**********************************
	 * TODO: methods
	 * slope() -> float or Vector2 to represent rise/run
	 * angle() -> ba::Angle with left to right horizontal
	 * 		line representing 0 degrees/0 radians while
	 * 		right-to-left represents 180 degrees/PI radians.
	 *
	***********************************/


public:
	Vector2<T>		p1{};
	Vector2<T>		p2{};
}; // class Line

// DEFINE COMMON TYPEDEFS
using IntLine 		= Line<int>;
using FloatLine		= Line<float>;

/********************************************
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Line<T>
*********************************************/
template <typename T>
constexpr Line<T>::Line() = default;

template <typename T>
constexpr Line<T>::Line(const Vector2<T>& _p1, const Vector2<T>& _p2) :
	p1(_p1),
	p2(_p2)
{

}

template <typename T>
constexpr Line<T>::Line(T x1, T y1, T x2, T y2) :
	p1(x1, y1),
	p2(x2, y2)
{

}

template <typename T>
template <typename U>
constexpr Line<T>::Line(const Line<U>& other) :
	p1(static_cast<Vector2<T>>(other.p1)),
	p2(static_cast<Vector2<T>>(other.p2))
{

}

template <typename T>
constexpr float Line<T>::length() const {
	return distance(p1, p2);
}

} // namespace ba
