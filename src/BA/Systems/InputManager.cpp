#include <BA/Systems/InputManager.hpp>

namespace ba {

void InputManager::handleEvents() {
	m_prevKeys = m_currKeys;
	m_currKeys.reset();

	int numkeys = 0;
	const std::uint8_t* keys = SDL_GetKeyboardState(&numkeys);

	for(int i = 0; i < numkeys; ++i) {
		if(keys[i] != 0) {
			m_currKeys.set(i);
		}
			
	}

	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		// switch(e.type) {
		// 	case SDL_KEYDOWN:
		// 		SDL_Scancode code = SDL_GetScancodeFromKey(e.key.keysym.sym);
		// 		m_currKeys.set(code);
		// 		break;
		// }
	}
}

bool InputManager::isKeyUp(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_prevKeys[code] && !m_currKeys[code];
}

bool InputManager::isKeyDown(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return !m_prevKeys[code] && m_currKeys[code];
}

bool InputManager::isKeyActive(SDL_KeyCode key) {
	SDL_Scancode code = SDL_GetScancodeFromKey(key);
	return m_currKeys[code];
}

Vector2i InputManager::getMousePos() const {
	Vector2i res;
	SDL_GetMouseState(&res.x, &res.y);

	return res;
}

}