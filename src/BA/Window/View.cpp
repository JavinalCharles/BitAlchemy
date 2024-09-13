#include <BA/Window/View.hpp>

namespace ba {

void View::setArea(const Vector2f& area) {
	m_viewport.setArea(area);
}
void View::setViewport(const FloatRect& viewport) {
	m_viewport = viewport;
}
void View::move(const Vector2f& offset) const {
	m_viewTL += offset;
}
void View::setCenter(const Vector2f& newCenter) const {
	setTopLeft(newCenter - (m_viewport.getArea() * 0.5f));
}
void View::setTopLeft(const Vector2f& newTL) const {
	m_viewTL = newTL;
}

} // namespace ba