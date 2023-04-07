#pragma once

#include <BA/Components/Component.hpp>
#include <BA/Utilities/Angle.hpp>
#include <BA/Utilities/Transform.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

class Transformable {
public:
	Transformable();

	virtual ~Transformable();

	void setPosition(const Vector2f& position);
	void setRotation(Angle angle);
	void setScale(const Vector2f& factors);
	void setOrigin(const Vector2f& origin);
	
	const Vector2f& getPosition() const;
	Angle getRotation() const;
	const Vector2f& getScale() const;
	const Vector2f& getOrigin() const;

	void move(const Vector2f& offset);
	void rotate(Angle angle);
	void scale(const Vector2f& factor);

	const Transform& getTransform() const;
	const Transform& getInverseTransform() const;

private:
	Vector2f			m_origin;
	Vector2f			m_position;
	Angle				m_rotation;
	Vector2f			m_scale{1.f, 1.f};
	mutable Transform 	m_transform;
	mutable Transform	m_inverseTransform;
	mutable bool		m_transformNeedUpdate{true};
	mutable bool 		m_inverseTransformNeedUpdate{true};

}; // class Transformable

} // namespace ba