#pragma once

#include "BA/Components/Timer.hpp"
#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

class TimerSystem : public ComponentSystem {
public:
	TimerSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);
	virtual void add(std::shared_ptr<Entity>& entity);
private:


}; // class ComponentSystem

} // namespace ba