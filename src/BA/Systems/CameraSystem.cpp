#include "BA/Systems/CameraSystem.hpp"
#include "BA/Systems/EntityManager.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

CameraSystem::CameraSystem(EntityManager* entityManager) :
	ComponentSystem::ComponentSystem(entityManager)
{

}

void CameraSystem::update(float) {
	for (auto& ID : this->getIDs()) {
		auto e = this->getEntity(ID);
		auto c = e->getComponent<Camera>();

		c->setViewCenter(e->getPosition());
		// e->CONTEXT->window->setView(c->getView());
	}
}

void CameraSystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getComponent<Camera>() != nullptr) {
		this->addID(entity->ID);
	}
}

} // namespace ba