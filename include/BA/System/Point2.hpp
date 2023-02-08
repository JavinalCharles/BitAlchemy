#pragma once

namespace ba {

template <typename T>
class Point2 {
public:
	T x;
	T y;

	Point2(T X, T Y);
	Point2();
	template <typename U>
	explicit Point2(const Point2<U>& other);

};

template<typename T>
Point2<T>::Point2(T X, T Y)
	: x(X), y(Y)
{

}

template<typename T>
Point2<T>::Point2()
	: x(), y() {

}

template <typename T>
template <typename U>
Point2<T>::Point2(const Point2<U>& other) 
	: x(other.x), y(other.y) {

}



// Define common types
using Point2i = 	Point2<int>;
using Point2f = 	Point2<float>;
using Point2u = 	Point2<unsigned int>;
using Point2d =		Point2<double>;
} // namespace ba