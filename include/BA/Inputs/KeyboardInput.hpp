#pragma once

#include <bitset>
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
	std::bitset<256> m_prevKeys;
	std::bitset<256> m_currKeys;
}; // class KeyboardInput

} // namespace ba