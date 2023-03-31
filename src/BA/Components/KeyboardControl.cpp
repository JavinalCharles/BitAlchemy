#include <BA/Components/KeyboardControl.hpp>
#include <BA/Entities/Entity.hpp>

namespace ba {

KeyboardControl::KeyboardControl(Entity* owner) :
	Component(owner)
{

}

void KeyboardControl::bindOnKeyActive(SDL_KeyCode key, KeyAction action) {
	if(m_keyActiveActions.contains(key)) {
		m_keyActiveActions.at(key).push_back(action);
	}
	else {
		m_keyActiveActions.insert(std::make_pair(key, std::vector<KeyAction>{action}));
	}
}

void KeyboardControl::bindOnKeyReleased(SDL_KeyCode key, KeyAction action) {
	if (m_keyReleasedActions.contains(key)) {
		m_keyReleasedActions.at(key).push_back(action);
	}
	else {
		m_keyReleasedActions.insert(std::make_pair(key, std::vector<KeyAction>{action}));
	}
}

void KeyboardControl::bindOnKeyPressed(SDL_KeyCode key, KeyAction action) {
	if (m_keyPressedActions.contains(key)) {
		m_keyPressedActions.at(key).push_back(action);
	}
	else {
		m_keyPressedActions.insert(std::make_pair(key, std::vector<KeyAction>{action}));
	}
}

const KeyBindings& KeyboardControl::getBindingsOnKeyPressed() const {
	return m_keyPressedActions;
}

const KeyBindings& KeyboardControl::getBindingsOnKeyReleased() const {
	return m_keyReleasedActions;
}

const KeyBindings& KeyboardControl::getBindingsOnKeyActive() const {
	return m_keyActiveActions;
}

} // namespace ba