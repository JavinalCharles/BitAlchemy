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

void ComponentSystem::add(std::vector<std::shared_ptr<Entity>>& entities) {
	for(std::shared_ptr<Entity>& e : entities) {
		this->add(e);
	}
}

void ComponentSystem::remove(unsigned entityID) {
	m_entityIDs.extract(entityID);
}

} // namespace ba