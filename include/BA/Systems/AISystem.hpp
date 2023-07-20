#pragma once 

#include "BA/Components/AI/AI.hpp"
#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

class AISystem : public ComponentSystem{
public:
	AISystem(EntityManager* entityManager);

	virtual void update(float deltaTime);

	virtual void add(std::shared_ptr<Entity>& entity);
private:

}; // class AISystem

} // namespace ba