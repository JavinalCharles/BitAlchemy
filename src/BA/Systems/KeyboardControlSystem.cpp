#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>

#include <iostream>

namespace ba {

KeyboardControlSystem::KeyboardControlSystem(EntityManager* entities) :
	ComponentSystem(entities)
{

}

void KeyboardControlSystem::update(float) {
	for(IDtype ID : m_entityIDs) {
		auto& e = m_entities->at(ID);

		auto kcs = e->getComponent<KeyboardControl>();
		auto& keyPressedBindings = kcs->getBindingsOnKeyPressed();
		for(auto& [key, actions] : keyPressedBindings) {
			if(m_keyInput->isKeyDown(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyReleasedBindings = kcs->getBindingsOnKeyReleased();
		for(auto& [key, actions] : keyReleasedBindings) {
			if(m_keyInput->isKeyUp(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyHeldBindings = kcs->getBindingsOnKeyActive();
		for(auto& [key, actions] : keyHeldBindings) {
			if(m_keyInput->isKeyActive(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
	}
}

// void KeyboardControlSystem::postUpdate(float) {

// }


void KeyboardControlSystem::add(std::shared_ptr<Entity>& entity) {
	if (entity->getComponent<KeyboardControl>() != nullptr) {
		this->addID(entity->ID);

		if (this->m_keyInput == nullptr) {
			this->m_keyInput = entity->CONTEXT->inputs->getInput<KeyboardInput>().get();
		}
	}
}

} // namespace ba