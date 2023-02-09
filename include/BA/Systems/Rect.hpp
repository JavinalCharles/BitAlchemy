#pragma once

#include <SDL2/SDL_rect.h>

namespace ba {

template <typename T>
struct Rect {
	T left;
	T top;
	T width;
	T height;

	Rect(T l = T(), T t = T(), w = T(), h = T());

	SDL_Rect toSDL_Rect();
};


template<typename T>
Rect<T>::Rect(T l, T t, T w, T h)
	: left(l),
	top(t),
	width(w),
	height(h)
{

}

template<typename T>
SDL_Rect Rect<T>::toSDL_Rect() {
	SDL_Rect res;
	res.x = left;
	res.y = top;
	res.w = width;
	res.h = height;

	return res;
}

// Common Typedefs

using Recti = Rect<int>;
using Rectf = Rect<float>;
using Rectd = Rect<double>;

} // namespace ba