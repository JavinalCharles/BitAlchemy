#include "BA/Inputs/KeyboardInput.hpp"
#include "BA/Inputs/InputManager.hpp"

namespace ba {

const IDtype KeyboardInput::IID = 1;

KeyboardInput::KeyboardInput(InputManager* im) :
	Input::Input(im)
{
	SDL_GetKeyboardState(&m_numKeys);
	m_prevKeys.resize(m_numKeys, false);
	m_currKeys.resize(m_numKeys, false);
}

void KeyboardInput::handleEvents() {
	m_prevKeys.swap(m_currKeys);

	const std::uint8_t* keys = SDL_GetKeyboardState(&m_numKeys);

	for(int i = 0; i < m_numKeys; ++i) {
		m_currKeys.at(i) = keys[i] > 0 ? true : false;
	}
}

bool KeyboardInput::isKeyUp(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_prevKeys.at(code) && !m_currKeys.at(code);
}

bool KeyboardInput::isKeyDown(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return !m_prevKeys.at(code) && m_currKeys.at(code);
}

bool KeyboardInput::isKeyActive(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_currKeys.at(code);
}



} // namespace ba