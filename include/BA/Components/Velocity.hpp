#pragma once

#include <BA/Components/Component.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

class Velocity : public Component {
public:
	Velocity(Entity* owner);

	void setMaxSpeed(float pixelsPerSecond);
	float getMaxSpeed() const;
	Vector2f getDirection() const;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void resetDirection();
private:
	float m_maxSpeed{};
	Vector2f m_direction{0,0};
}; // class Velocity


} // namespace ba