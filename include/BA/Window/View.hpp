#pragma once

#include <BA/Utilities/Angle.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Transform.hpp>

namespace ba {

class View {
public:
	View();
	View(const Vector2f& area, const Vector2f& center);
	View(const FloatRect& rectangle);

	const Vector2f& getCenter() const;
	const Vector2f& getArea() const;
	const FloatRect& getViewport() const;
	const Angle& getRotation() const;

	void setCenter(const Vector2f& center);
	void setArea(const Vector2f& area);
	void setRotation(const Angle& angle);
	void setViewport(const FloatRect& viewport);

	void reset(const FloatRect& rectangle);
	void move(const Vector2f& offset);
	void rotate(Angle angle);
	void zoom(float factor);

	const Transform& getTransform() const;
	const Transform& getInverseTransform() const;

private:
	Vector2f 	m_center;
	Vector2f 	m_area;
	Angle 		m_rotation;

	FloatRect 	m_viewport{{0, 0}, {1, 1}};

	mutable Transform 	m_transform;

	mutable Transform 	m_inverseTransform;

	mutable bool 		m_transformUpdated{false};
	mutable bool		m_inverseTransformUpdated{false};
}; // class View

} // namespace ba