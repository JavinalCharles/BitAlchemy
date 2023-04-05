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
	return Pi * (radius * radius);
}

template <typename T>
constexpr double Circle<T>::circumference() const {
	return 2 * radius * Pi;
}

template <typename T>
bool Circle<T>::intersects(const Circle<T>& other) const {
	return origin.distance(other.origin) <= (this->radius + other.radius);
}