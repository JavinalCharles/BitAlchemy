#include <BA/Components/Velocity.hpp>
#include <BA/Entities/Entity.hpp>

#include <iostream>

namespace ba {

Velocity::Velocity(Entity* owner) :
	Component(owner)
{

}

void Velocity::setMax(const Vector2f& maxVelocity) {
	m_maxVelocity = maxVelocity;
}

const Vector2f& Velocity::getMax() const {
	return m_maxVelocity;
}

void Velocity::set(const Vector2f& velocity) {
	m_velocity = velocity;
	clampVelocity();
}

void Velocity::set(float x, float y) {
	m_velocity.x = x;
	m_velocity.y = y;
	clampVelocity();
}

void Velocity::setX(float x) {
	m_velocity.x = x;
	clampVelocity();
}

void Velocity::setY(float y) {
	m_velocity.y = y;
	clampVelocity();
}

const Vector2f& Velocity::get() const {
	return m_velocity;
}

void Velocity::resetVelocity() {
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}

void Velocity::moveUp() {
	m_velocity.y = -m_maxVelocity.y;
}

void Velocity::moveRight() {
	m_velocity.x = m_maxVelocity.x;
	std::clog << "Moving Right. " << m_velocity.x << "\n";
}

void Velocity::moveDown() {
	m_velocity.y = m_maxVelocity.y;
	
}

void Velocity::moveLeft() {
	m_velocity.x = -m_maxVelocity.x;
}


void Velocity::clampVelocity() {
	if (std::fabs(m_velocity.x) > m_maxVelocity.x)
	{
		if(m_velocity.x > 0)
		{
			m_velocity.x = m_maxVelocity.x;
		}
		else
		{
			m_velocity.x = -m_maxVelocity.x;
		}
	}

	if (std::fabs(m_velocity.y) > m_maxVelocity.y)
	{
		if (m_velocity.y > 0.f)
		{
			m_velocity.y = m_maxVelocity.y;
		}
		else
		{
			m_velocity.y = - m_maxVelocity.y;
		}
	}
}

} // namespace ba