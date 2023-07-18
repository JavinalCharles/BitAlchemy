#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>

#include <iostream>

namespace ba {

KeyboardControlSystem::KeyboardControlSystem(EntityManager* entities) :
	ComponentSystem(entities)
{

}

void KeyboardControlSystem::update(float) {
	std::shared_ptr<KeyboardInput> keyboard = nullptr;
	for(unsigned ID : m_entityIDs) {
		auto& e = m_entities->at(ID);
		if (keyboard == nullptr) {
			keyboard = e->CONTEXT->inputs->getInput<KeyboardInput>();
		}

		auto kcs = e->getComponent<KeyboardControl>();
		auto& keyPressedBindings = kcs->getBindingsOnKeyPressed();
		for(auto& [key, actions] : keyPressedBindings) {
			if(keyboard->isKeyDown(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyReleasedBindings = kcs->getBindingsOnKeyReleased();
		for(auto& [key, actions] : keyReleasedBindings) {
			if(keyboard->isKeyUp(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyHeldBindings = kcs->getBindingsOnKeyActive();
		for(auto& [key, actions] : keyHeldBindings) {
			if(keyboard->isKeyActive(key)) {
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
	auto keyboardControl = entity->getComponent<KeyboardControl>();
	if (keyboardControl != nullptr) {
		m_entityIDs.insert(entity->ID);
	}
}

} // namespace ba