#pragma once

#include <BA/Components/Velocity.hpp>
#include <BA/Systems/ComponentSystem.hpp>

namespace ba {

class MovementSystem : public ComponentSystem {
public:
	MovementSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);

}; // class MovementSystem

} // namespace ba