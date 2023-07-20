#include "BA/Systems/AISystem.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Systems/EntityManager.hpp"
#include <BA/Components/AI/AI.hpp>

namespace ba {

AISystem::AISystem(EntityManager* entityManager) :
	ComponentSystem::ComponentSystem(entityManager)
{

}

void AISystem::update(float deltaTime) {
	for (const auto& ID: this->getIDs()) {
		this->getEntity(ID)->getComponent<ba::AI>()->behave(deltaTime);
	}
}

void AISystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getComponent<ba::AI>() != nullptr) {
		m_entityIDs.insert(entity->ID);
	}
}

} // namespace ba