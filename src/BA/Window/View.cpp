#include <BA/Window/View.hpp>

#include <cmath>

namespace ba {

View::View() {
	reset(FloatRect({0, 0}, {1000, 1000}));
}

View::View(const Vector2f& area, const Vector2f& center) 
	: m_center(center),
	m_area(area)
{

}

View::View(const FloatRect& rectangle) {
	reset(rectangle);
}



void View::setCenter(const Vector2f& center) {
	m_center = center;
	m_transformUpdated = false;
	m_inverseTransformUpdated = false;
}

void View::setArea(const Vector2f& area) {
	m_area = area;

	m_transformUpdated = false;
	m_inverseTransformUpdated = false;
}

void View::setRotation(const Angle& angle) {
	m_rotation = angle.wrapUnsigned();

	m_transformUpdated = false;
	m_inverseTransformUpdated = false;
}

void View::setViewport(const FloatRect& viewport) {
	m_viewport = viewport;
}

void View::reset(const FloatRect& rectangle) {
	m_center.x = rectangle.l + rectangle.w / 2.f;
	m_center.y = rectangle.t + rectangle.h / 2.f;

	m_area.x = rectangle.w;
	m_area.y = rectangle.h;

	m_rotation = Angle::Zero;

	m_transformUpdated = false;
	m_inverseTransformUpdated = false;
}

const Vector2f& View::getCenter() const {
	return m_center;
}

const Vector2f& View::getArea() const {
	return m_area;
}

const Angle& View::getRotation() const {
	return m_rotation;
}

const FloatRect& View::getViewport() const {
	return m_viewport;
}

void View::move(const Vector2f& offset) {
	setCenter(m_center + offset);
}

void View::rotate(Angle angle) {
	setRotation(m_rotation + angle);
}

void View::zoom(float factor) {
	setArea(m_area * factor);
}

const Transform& View::getTransform() const {
	if (!m_transformUpdated) {
		float angle = m_rotation.asRadians();
		float cosine = std::cos(angle);
		float sine = std::sin(angle);
		float tx = -m_center.x * cosine - m_center.y * sine + m_center.x;
		float ty = m_center.x * sine - m_center.y * cosine + m_center.y;

		float a = 2.f / m_area.x;
		float b = -2.f / m_area.y;
		float c = -a * m_center.x;
		float d = -b * m_center.y;

		m_transform = Transform(
			 a * cosine, a * sine,   a * tx + c,
			-b * sine,   b * cosine, b * ty + d,
			 0.f,        0.f,        1.f
		);
		m_transformUpdated = true;
	}

	return m_transform;
}

const Transform& View::getInverseTransform() const {
	if (!m_inverseTransformUpdated) {
		m_inverseTransform = getTransform().getInverse();
		m_inverseTransformUpdated = true;
	}

	return m_inverseTransform;
}


} // namespace ba