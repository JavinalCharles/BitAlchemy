#pragma once

namespace ba {

class InputManager;

class Input {
public:
	Input(InputManager* im);

	virtual void handleEvents() = 0;

private:
	InputManager* m_im;
}; // class Input

} // namespace ba