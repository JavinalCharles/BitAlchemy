#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>

namespace ba {

KeyboardControlSystem::KeyboardControlSystem(EntityManager* entities) :
	ComponentSystem(entities)
{

}

void KeyboardControlSystem::update(float) {
	for(unsigned ID : m_entityIDs) {
		auto& e = m_entities->at(ID);

		auto kcs = e->getComponent<KeyboardControl>();
		auto& keyPressedBindings = kcs->getBindingsOnKeyPressed();
		for(auto& [key, actions] : keyPressedBindings) {
			if(e->CONTEXT->inputs->isKeyDown(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyReleasedBindings = kcs->getBindingsOnKeyReleased();
		for(auto& [key, actions] : keyReleasedBindings) {
			if(e->CONTEXT->inputs->isKeyUp(key)) {
				for(auto& action: actions) {
					action();
				}
			}
		}
		auto& keyHeldBindings = kcs->getBindingsOnKeyHeld();
		for(auto& [key, actions] : keyHeldBindings) {
			if(e->CONTEXT->inputs->isKeyHeld(key)) {
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