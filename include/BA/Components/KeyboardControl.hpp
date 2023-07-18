#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <BA/Components/Component.hpp>
#include <BA/Inputs/InputManager.hpp>
#include <BA/Inputs/KeyboardInput.hpp>

namespace ba {

using KeyAction = std::function<void(void)>;

using KeyBindings = std::unordered_map<SDL_KeyCode, std::vector<KeyAction>>;

class KeyboardControl : public Component {
public:
	KeyboardControl(Entity* owner);

	void bindOnKeyActive(SDL_KeyCode key, KeyAction action);
	void bindOnKeyReleased(SDL_KeyCode key, KeyAction action);
	void bindOnKeyPressed(SDL_KeyCode key, KeyAction action);

	const KeyBindings& getBindingsOnKeyPressed() const;
	const KeyBindings& getBindingsOnKeyReleased() const;
	const KeyBindings& getBindingsOnKeyActive() const;

private:
	KeyBindings 	m_keyPressedActions;
	KeyBindings 	m_keyActiveActions;
	KeyBindings 	m_keyReleasedActions;
public:
	static const IDtype CID;

}; // class KeyboardControl

} // namespace ba