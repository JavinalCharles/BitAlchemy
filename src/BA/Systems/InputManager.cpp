#include <BA/Systems/InputManager.hpp>

namespace ba {

void InputManager::handleEvents() {
	m_prevKeys = m_currKeys;
	m_currKeys.reset();

	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_KEYDOWN:
				m_currKeys.set(e.key.keysym.sym);
				break;
		}
	}
}

bool InputManager::isKeyUp(SDL_KeyCode key) {
	return m_prevKeys[key] && !m_currKeys[key];
}

bool InputManager::isKeyDown(SDL_KeyCode key) {
	return m_currKeys[key];
}

bool InputManager::isKeyHeld(SDL_KeyCode key) {
	return m_prevKeys[key] && m_currKeys[key];
}


}