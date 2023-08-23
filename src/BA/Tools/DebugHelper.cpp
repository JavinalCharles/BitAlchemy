#include "BA/Tools/DebugHelper.hpp"

ba::DebugHelper ba::debug;

namespace ba {

DebugHelper::DebugHelper(std::basic_streambuf<wchar_t, std::char_traits<wchar_t>>* sb) :
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>::basic_ostream(sb)
{

}

// void DebugHelper::drawRect(const FloatRect& rect) {
// 	m_rects.push_back(rect);
// }

// void DebugHelper::drawPoint(const FloatRect& point) {

// }

DebugHelper& DebugHelper::operator<<(const IntRect& rect) {
	m_rects.push_back(rect);
	return *this;
}

DebugHelper& DebugHelper::operator<<(const IntLine& line) {
	m_lines.push_back(line);
	return *this;
}

DebugHelper& DebugHelper::operator<<(const Vector2f& point) {
	m_points.push_back(point);
	return *this;
}



void DebugHelper::draw(Window& window) {
#ifdef DEBUG_MODE_ON

	for (auto& rect : m_rects) {
		window.drawRect(rect, m_color);
	}
	for (auto& line : m_lines) {
		window.drawLine(line, m_color);
	}
	for (auto& point : m_points) {
		window.drawPoint(point, m_color);
	}

	m_rects.clear();
	m_lines.clear();
	m_points.clear();

#endif
}

void DebugHelper::setColor(const Color& color) {
	m_color = color;
}

} // namespace ba
