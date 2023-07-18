#include <BA/Inputs/MouseInput.hpp>
#include <BA/Inputs/InputManager.hpp>

namespace ba {

const IDtype MouseInput::IID = 2;

MouseInput::MouseInput(InputManager* im) :
	Input::Input(im)
{

}

void MouseInput::handleEvents() {
	m_prevMousePos = m_currMousePos;
	m_prevMouseButtons = m_currMouseButtons;

	m_currMouseButtons = SDL_GetMouseState(&m_currMousePos.x, &m_currMousePos.y);
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

} // namespace ba