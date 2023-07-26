#pragma once

#include <vector>
#include <SDL2/SDL_events.h>

#include <BA/Inputs/Input.hpp>
#include <BA/Types.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace ba {

class KeyboardInput : public Input {
public:
	static const IDtype IID;

	KeyboardInput(InputManager* im);

	virtual void handleEvents();

	bool isKeyUp(SDL_KeyCode key);
	bool isKeyDown(SDL_KeyCode key);
	bool isKeyActive(SDL_KeyCode key);
private:
	std::vector<bool> m_prevKeys;
	std::vector<bool> m_currKeys;
	int m_numKeys;
}; // class KeyboardInput

} // namespace ba