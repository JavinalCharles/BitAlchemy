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


	constexpr Vector2<T> getPosition() const;
	constexpr Vector2<T> getArea() const;
	constexpr bool contains(const Vector2<T>& point) const;
	constexpr std::optional<Rect<T>> intersects(const Rect<T>& rect) const;


	template <typename U>
	constexpr Rect<T>& operator=(const Rect<U>& rhs);

	constexpr SDL_Rect toSDL_Rect() const;
}; // class Rect


#include "BA/Utilities/Rect.inl"

// COMMON TYPEDEFS
using FloatRect = ba::Rect<float>;
using IntRect = ba::Rect<int>;

}; // namespace ba