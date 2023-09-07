#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "BA/Utilities/Color.hpp"
#include "BA/Utilities/Line.hpp"
#include "BA/Utilities/Rect.hpp"
#include "BA/Utilities/Vector2.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class DebugHelper : public std::basic_ostream<wchar_t, std::char_traits<wchar_t>> {
public:
	explicit DebugHelper(std::basic_streambuf<wchar_t, std::char_traits<wchar_t>>* sb = std::wclog.rdbuf());

	DebugHelper& operator<<(const IntRect& rect);
	DebugHelper& operator<<(const IntLine& line);
	DebugHelper& operator<<(const Vector2f& point);

	void draw(Window& window);
	void setColor(const Color& color);
private:
	std::vector<IntRect>	m_rects;
	std::vector<IntLine> 	m_lines;
	std::vector<Vector2f>	m_points;


	Color 					m_color = Color::Blue;
}; // class DebugHelper;

extern DebugHelper debug;

} // namespace ba
