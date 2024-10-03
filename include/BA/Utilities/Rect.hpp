#pragma once

#include <optional>
#include <SDL2/SDL_rect.h>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

template <typename T>
class Rect {
public: // ATTRIBUTES
	T l{}; // left
	T t{}; // top
	T w{}; // width
	T h{}; // height

public: // METHODS & CONSTRUCTORS
	constexpr Rect();
	constexpr Rect(T left, T top, T width, T height);
	constexpr Rect(const Vector2<T>& topLeft, const Vector2<T>& dimension);
	template <typename U>
	constexpr Rect(const Rect<U>& otherRect);

	constexpr void setPosition(const Vector2<T>& pos);
	constexpr void setArea(const Vector2<T>& size);

	constexpr Vector2<T> getPosition() const;
	constexpr Vector2<T> getArea() const;
	constexpr bool contains(const Vector2<T>& point) const;
	constexpr std::optional<Rect<T>> intersects(const Rect<T>& rect) const;


	template <typename U>
	constexpr Rect<T>& operator=(const Rect<U>& rhs);

	constexpr SDL_Rect toSDL_Rect() const;

	constexpr SDL_FRect toSDL_FRect() const;
}; // class Rect

// COMMON TYPEDEFS
using FloatRect = ba::Rect<float>;
using IntRect = ba::Rect<int>;


/**
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Rect<T>
**/
namespace {
	/**
	 * functions just to avoid adding cmath
	**/
	template <typename T>
	constexpr T min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template <typename T>
	constexpr T max(const T& a, const T& b) {
		return a > b ? a : b;
	}
} // anonymous namespace

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
constexpr void Rect<T>::setPosition(const Vector2<T>& pos) {
	this->l = pos.x;
	this->t = pos.y;
}

template<typename T>
constexpr void Rect<T>::setArea(const Vector2<T>& size) {
	this->w = size.x;
	this->h = size.y;
}

template <typename T>
constexpr Vector2<T> Rect<T>::getPosition() const {
	return {l, t};
}

template <typename T>
constexpr Vector2<T> Rect<T>::getArea() const {
	return {w, h};
}


template <typename T>
constexpr bool Rect<T>::contains(const Vector2<T>& point) const {
	const T minX = min(l, static_cast<T>(l + w));
	const T maxX = max(l, static_cast<T>(l + w));
	const T minY = min(t, static_cast<T>(t + h));
	const T maxY = max(t, static_cast<T>(t + h));

	return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}

template <typename T>
constexpr std::optional<Rect<T>> Rect<T>::intersects(const Rect<T>& rect) const {
	const T r1minX = min(l, static_cast<T>(l + w));
	const T r1maxX = max(l, static_cast<T>(l + w));
	const T r1minY = min(t, static_cast<T>(t + h));
	const T r1maxY = max(t, static_cast<T>(t + h));

	const T r2minX = min(rect.l, static_cast<T>(rect.l + rect.w));
	const T r2maxX = max(rect.l, static_cast<T>(rect.l + rect.w));
	const T r2minY = min(rect.t, static_cast<T>(rect.t + rect.h));
	const T r2maxY = max(rect.t, static_cast<T>(rect.t + rect.h));

	const T interLeft = max(r1minX, r2minX);
	const T interTop = max(r1minY, r2minY);
	const T interRight = min(r1maxX, r2maxX);
	const T interBottom = min(r1maxY, r2maxY);

	if (interLeft < interRight && interTop < interBottom) {
		return std::make_optional<Rect<T>>({
			{interLeft, interTop},
			{interRight - interLeft, interBottom - interTop}
		});
	}
	else {
		return std::nullopt;
	}
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
		static_cast<int>((l <= (l+w)) ? l : l+w),
		static_cast<int>((t <= (t+h)) ? t : t+h),
		static_cast<int>((w >= 0) ? w : -w),
		static_cast<int>((h >= 0) ? h : -h)
	};
}

template <typename T>
constexpr SDL_FRect Rect<T>::toSDL_FRect() const {
	return SDL_FRect{
		static_cast<float>((l <= (l+w)) ? l : l+w),
		static_cast<float>((t <= (t+h)) ? t : t+h),
		static_cast<float>((w >= 0) ? w : -w),
		static_cast<float>((h >= 0) ? h : -h)
	};
}

}; // namespace ba
