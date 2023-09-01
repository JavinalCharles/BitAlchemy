#include "BA/Systems/AISystem.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Systems/EntityManager.hpp"
#include <BA/Components/AI/AI.hpp>

#include "BA/Tools/DebugHelper.hpp"

namespace ba {

AISystem::AISystem(EntityManager* entityManager) :
	ComponentSystem::ComponentSystem(entityManager)
{

}

void AISystem::update(float deltaTime) {
	for (const auto& ID: this->getIDs()) {
		this->getEntity(ID)->getAI()->behave(deltaTime);
	}
}

void AISystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getAI() != nullptr) {
		// ba::debug << "Found an entity with A.I. Entity ID: " << entity->ID << std::endl;
		m_entityIDs.insert(entity->ID);
	}
}

} // namespace ba
