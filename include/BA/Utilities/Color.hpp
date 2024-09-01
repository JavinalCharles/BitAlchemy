#pragma once

#include <cstdint>
#include <SDL2/SDL_pixels.h>

namespace ba {

class Color {
public: // static attributes
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Transparent;

public: // attributes
	std::uint8_t r{};
	std::uint8_t g{};
	std::uint8_t b{};
	std::uint8_t a{};

public:
	constexpr Color();

	constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);
	constexpr Color(std::uint32_t color);

	constexpr SDL_Color toSDL_Color() const;

}; // class Color

/**
 * BELOW ARE METHODS AND FUNCTIONS
 * IMPLEMENTATIONS FOR CLASS Color.
**/
constexpr Color::Color() = default;

constexpr Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
	: r(red),
	g(green),
	b(blue),
	a(alpha)
{

}

constexpr Color::Color(std::uint32_t color)
	: r(static_cast<std::uint8_t>((color & 0xff000000) >> 24)),
	g(static_cast<std::uint8_t>((color & 0x00ff0000) >> 16)),
	b(static_cast<std::uint8_t>((color & 0x0000ff00) >> 8)),
	a(static_cast<std::uint8_t>(color & 0x000000ff))
{

}

constexpr SDL_Color Color::toSDL_Color() const {
	return SDL_Color {
		r, g, b, a
	};
}

constexpr Color Color::Black(0, 0, 0);
constexpr Color Color::White(255, 255, 255);
constexpr Color Color::Red(255, 0, 0);
constexpr Color Color::Green(0, 255, 0);
constexpr Color Color::Blue(0, 0, 255);
constexpr Color Color::Yellow(255, 255, 0);
constexpr Color Color::Magenta(255, 0, 255);
constexpr Color Color::Cyan(0, 255, 255);
constexpr Color Color::Transparent(0, 0, 0, 0);

} // namespace ba
