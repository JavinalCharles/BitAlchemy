#include "BA/Systems/MouseControlSystem.hpp"
#include "BA/Systems/EntityManager.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

MouseControlSystem::MouseControlSystem(EntityManager* entities) :
	ComponentSystem(entities)
{

}

void MouseControlSystem::update(float) {
	for (IDtype ID : m_entityIDs) {
		auto e = this->getEntity(ID);
		if (e == nullptr) {
			continue;
		}

		auto mis = e->getComponent<MouseControl>();
		for (auto& [btn, actions] : mis->getBindingsOnMouseButtonPressed()) {
			if (m_mouseInput->isButtonDown(btn)) {
				for (auto& action : actions) {
					action();
				}
			}
		}

		for (auto& [btn, actions] : mis->getBindingsOnMouseButtonReleased()) {
			if (m_mouseInput->isButtonUp(btn)) {
				for (auto& action : actions) {
					action();
				}
			}
		}

		for (auto& [btn, actions] : mis->getBindingsOnMouseButtonActive()) {
			if (m_mouseInput->isButtonActive(btn)) {
				for (auto& action : actions) {
					action();
				}
			}
		}
	}

}

void MouseControlSystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getComponent<MouseControl>() != nullptr) {
		this->addID(entity->ID);

		if (this->m_mouseInput == nullptr) {
			this->m_mouseInput = entity->CONTEXT->inputs->getInput<MouseInput>().get();
		}
	}
}

} // namespace ba