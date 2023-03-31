#pragma once

#include <BA/Components/KeyboardControl.hpp>
#include <BA/Systems/ComponentSystem.hpp>

namespace ba {

class KeyboardControlSystem : public ComponentSystem {
public:
	KeyboardControlSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);
	// virtual void postUpdate(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);

}; // class KeyboardControlSystem

} // namespace ba
