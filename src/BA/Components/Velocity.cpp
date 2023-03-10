#include <BA/Components/Velocity.hpp>
#include <BA/Entities/Entity.hpp>

namespace ba {

Velocity::Velocity(Entity* owner) :
	Component(owner)
{

}

void Velocity::setMaxSpeed(float pixelsPerSecond) {
	m_maxSpeed = pixelsPerSecond;
}

float Velocity::getMaxSpeed() const {
	return m_maxSpeed;
}

Vector2f Velocity::getDirection() const{
	return m_direction;
}

void Velocity::moveUp() {
	m_direction.y -= m_maxSpeed;
}

void Velocity::moveDown() {
	m_direction.y += m_maxSpeed;
}

void Velocity::moveLeft() {
	m_direction.x -= m_maxSpeed;
}

void Velocity::moveRight() {
	m_direction.x += m_maxSpeed;
}

void Velocity::resetDirection() {
	m_direction.x = 0.f;
	m_direction.y = 0.f;
}


} // namespace ba