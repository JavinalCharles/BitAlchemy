#include "BA/Inputs/KeyboardInput.hpp"
#include "BA/Inputs/InputManager.hpp"

namespace ba {

const IDtype KeyboardInput::IID = 1;

KeyboardInput::KeyboardInput(InputManager* im) :
	Input::Input(im)
{

}

void KeyboardInput::handleEvents() {
	m_prevKeys = m_currKeys;
	m_currKeys.reset();

	int numkeys = 0;
	const std::uint8_t* keys = SDL_GetKeyboardState(&numkeys);

	for(int i = 0; i < numkeys; ++i) {
		if(keys[i] != 0) {
			m_currKeys.set(i);
		}		
	}
}

bool KeyboardInput::isKeyUp(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_prevKeys[code] && !m_currKeys[code];
}

bool KeyboardInput::isKeyDown(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return !m_prevKeys[code] && m_currKeys[code];
}

bool KeyboardInput::isKeyActive(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_currKeys[code];
}



} // namespace ba