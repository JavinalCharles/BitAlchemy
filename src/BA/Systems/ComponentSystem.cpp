#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

ComponentSystem::ComponentSystem(ba::EntityManager* entityManager)
	: m_entities(entityManager)
{
	
}

void ComponentSystem::update(float deltaTime) {

}

void ComponentSystem::postUpdate(float deltaTime) {
	
}

} // namespace ba