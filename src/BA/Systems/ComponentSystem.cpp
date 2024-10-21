#include "BA/Systems/ComponentSystem.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Systems/EntityManager.hpp"

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

void ComponentSystem::remove(IDtype entityID) {
	if (m_entityIDs.contains(entityID)) {
		m_entityIDs.extract(entityID);
	}
}

std::shared_ptr<Entity> ComponentSystem::getEntity(IDtype id) const {
	try {
		return m_entities->at(id);
	}
	catch (const std::out_of_range&) {
		return nullptr;
	}
}

const std::set<IDtype>& ComponentSystem::getIDs() const {
	return m_entityIDs;
}

void ComponentSystem::addID(IDtype entityID){
	m_entityIDs.insert(entityID);
}

} // namespace ba