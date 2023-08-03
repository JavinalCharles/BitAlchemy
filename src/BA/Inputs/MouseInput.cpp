#include <BA/Inputs/MouseInput.hpp>
#include <BA/Inputs/InputManager.hpp>

namespace ba {

const IDtype MouseInput::IID = 2;

const float MouseInput::NEVER_CLICKED = -1.f;

MouseInput::MouseInput(InputManager* im) :
	Input::Input(im)
{

}

void MouseInput::handleEvents() {
	m_prevMousePos = m_currMousePos;
	m_prevMouseButtons = m_currMouseButtons;

	m_currMouseButtons = SDL_GetMouseState(&m_currMousePos.x, &m_currMousePos.y);

	SDL_Event e[1];

	while(SDL_PeepEvents(e, 1, SDL_GETEVENT, SDL_MOUSEMOTION, SDL_MOUSEWHEEL) > 0) {
		switch(e[0].type) {
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				this->m_lastClicked.insert_or_assign(static_cast<uint32>(1u << (e[0].button.button - 1u)), SDL_GetPerformanceCounter());
				break;
			case SDL_MOUSEMOTION:
				// TODO
				break;
			case SDL_MOUSEWHEEL:
				// TODO
				break;
		}
	}
}

const Vector2i& MouseInput::getPrevMousePos() const {
	return m_prevMousePos;
}

const Vector2i& MouseInput::getCurrMousePos() const {
	return m_currMousePos;
}

bool MouseInput::isButtonUp(MouseButton button) const {
	std::uint32_t btn = static_cast<std::uint32_t>(button);
	return (m_prevMouseButtons & btn) && !(m_currMouseButtons & btn);
}

bool MouseInput::isButtonDown(MouseButton button) const {
	std::uint32_t btn = static_cast<std::uint32_t>(button);
	return !(m_prevMouseButtons & btn) && (m_currMouseButtons & btn);
}

bool MouseInput::isButtonActive(MouseButton button) const {
	std::uint32_t btn = static_cast<std::uint32_t>(button);
	return m_currMouseButtons & btn;
}

float MouseInput::timeSinceLastClicked(MouseButton button) const {
	ba::uint32 btn = static_cast<ba::uint32>(button);
	if (!m_lastClicked.contains(btn)) {
		return NEVER_CLICKED;
	}
	ba::uint64 elapsedTime = SDL_GetPerformanceCounter() - m_lastClicked.at(btn);
	// return as seconds;
	return elapsedTime / static_cast<float>(SDL_GetPerformanceFrequency());
}

} // namespace ba