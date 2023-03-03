#include "BA/Systems/ComponentSystem.hpp"

namespace ba {

ComponentSystem::ComponentSystem(ba::EntityManager* entityManager)
	: m_entities(entityManager)
{
	
}

void ComponentSystem::update(float) {

}

void ComponentSystem::postUpdate(float) {
	
}

void ComponentSystem::remove(unsigned entityID) {
	m_entityIDs.extract(entityID);
}

} // namespace ba