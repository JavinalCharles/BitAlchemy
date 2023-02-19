#include <BA/Components/Transformable.hpp>
#include <BA/Entities/Entity.hpp>

namespace ba {

Transformable::Transformable(Entity* owner) 
	: Component(owner)
{
	
}


Transformable::~Transformable() = default;

void Transformable::setPosition(const Vector2f& position) {
	m_position = position;
	m_transformNeedUpdate = true;
	m_inverseTransformNeedUpdate = true;
}

void Transformable::setRotation(Angle angle) {
	m_rotation = angle.wrapUnsigned();
	m_transformNeedUpdate = true;
	m_inverseTransformNeedUpdate = true;
}

void Transformable::setScale(const Vector2f& factors) {
	m_scale = factors;
	m_transformNeedUpdate = true;
	m_inverseTransformNeedUpdate = true;
}

void Transformable::setOrigin(const Vector2f& origin) {
	m_origin = origin;
	m_transformNeedUpdate = true;
	m_inverseTransformNeedUpdate = true;
}

const Vector2f& Transformable::getPosition() const {
	return m_position;
}

Angle Transformable::getRotation() const {
	return m_rotation;
}

const Vector2f& Transformable::getScale() const {
	return m_scale;
}

const Vector2f& Transformable::getOrigin() const {
	return m_origin;
}

void Transformable::move(const Vector2f& offset) {
	setPosition(m_position + offset);
}

void Transformable::rotate(Angle angle) {
	setRotation(m_rotation + angle);
}

void Transformable::scale(const Vector2f& factor) {
	setScale({m_scale.x * factor.x, m_scale.y * factor.y});
}

const Transform& Transformable::getTransform() const {
	if (m_transformNeedUpdate) {
		float angle 	= -m_rotation.asRadians();
		float cosine	= std::cos(angle);
		float sine		= std::sin(angle);
		float sxc		= m_scale.x * cosine;
		float syc		= m_scale.y * cosine;
		float sxs		= m_scale.x * sine;
		float sys		= m_scale.y * sine;
		float tx		= -m_origin.x * sxc - m_origin.y * sys + m_position.x;
		float ty		= m_origin.x * sxs - m_origin.y * syc + m_position.y;

		m_transform = Transform(
			 sxc, sys, tx,
			-sxs, syc, ty,
			 0.f, 0.f, 1.f
		);

		m_transformNeedUpdate = false;
	}

	return m_transform;
}

const Transform& Transformable::getInverseTransform() const {
	if (m_inverseTransformNeedUpdate) {
		m_inverseTransform = getTransform().getInverse();
		m_inverseTransformNeedUpdate = false;
	}

	return m_inverseTransform;
}

} // namespace ba