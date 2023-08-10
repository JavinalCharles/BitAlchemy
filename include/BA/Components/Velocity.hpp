#pragma once

#include <BA/Components/Component.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

class Velocity : public Component {
public:
	explicit Velocity(Entity* owner);

	void setMax(const Vector2f& maxVelocity);
	const Vector2f& getMax() const;

	void set(const Vector2f& vel);
	void set(float x, float y);
	void setX(float x);
	void setY(float y);

	const Vector2f& get() const;

	void resetVelocity();

	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
private:
	void clampVelocity();

	Vector2f m_velocity{};
	Vector2f m_maxVelocity{600.f,600.f};

public:
	static const IDtype CID;
}; // class Velocity


} // namespace ba
