#pragma once

#include "BA/Components/MouseControl.hpp"
#include "BA/Inputs/MouseInput.hpp"
#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

class MouseControlSystem : public ComponentSystem {
public:
	explicit MouseControlSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);
private:
	MouseInput* m_mouseInput = nullptr;

}; // class ComponentSystem

} // namespace ba
