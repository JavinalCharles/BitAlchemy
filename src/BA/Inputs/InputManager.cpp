#include <BA/Inputs/InputManager.hpp>

namespace ba {

InputManager::~InputManager() {
	m_inputs.clear();
}

void InputManager::handleEvents() {
	for(auto& [id, input] : m_inputs) {
		input->handleEvents();
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

// Vector2i InputManager::getMousePos() const {
// 	Vector2i res;
// 	SDL_GetMouseState(&res.x, &res.y);

// 	return res;
// }

}