template <typename T>
constexpr Rect<T>::Rect() = default;

template <typename T>
constexpr Rect<T>::Rect(const Vector2<T>& topLeft, const Vector2<T>& dimension) :
	l(topLeft.x),
	t(topLeft.y),
	w(dimension.x),
	h(dimension.y)
{
	
}

template <typename T>
constexpr Rect<T>::Rect(T left, T top, T width, T height)  :
	l(left), 
	t(top), 
	w(width), 
	h(height)
{

}

template <typename T>
template <typename U>
constexpr Rect<T>::Rect(const Rect<U>& otherRect) :
	l(static_cast<T>(otherRect.l)),
	t(static_cast<T>(otherRect.t)),
	w(static_cast<T>(otherRect.w)),
	h(static_cast<T>(otherRect.h))
{

}

template <typename T>
template <typename U>
constexpr Rect<T>& Rect<T>::operator=(const Rect<U>& rhs) {
	l = static_cast<T>(rhs.l);
	t = static_cast<T>(rhs.t);
	w = static_cast<T>(rhs.w);
	h = static_cast<T>(rhs.h);

	return *this;
}


template <typename T>
constexpr SDL_Rect Rect<T>::toSDL_Rect() const {
	return SDL_Rect{
		static_cast<int>(l), 
		static_cast<int>(t), 
		static_cast<int>(w), 
		static_cast<int>(h)
	};
}