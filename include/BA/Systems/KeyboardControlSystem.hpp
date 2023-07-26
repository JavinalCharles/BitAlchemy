#pragma once

#include <BA/Components/KeyboardControl.hpp>
#include <BA/Inputs/KeyboardInput.hpp>
#include <BA/Systems/ComponentSystem.hpp>

namespace ba {

class KeyboardControlSystem : public ComponentSystem {
public:
	KeyboardControlSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);
	// virtual void postUpdate(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);
private:
	std::shared_ptr<KeyboardInput> m_keyInput = nullptr;

}; // class KeyboardControlSystem

} // namespace ba
