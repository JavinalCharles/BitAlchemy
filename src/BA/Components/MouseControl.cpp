#include "BA/Components/MouseControl.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

const IDtype MouseControl::CID = ComponentID::MOUSE_CONTROL;

MouseControl::MouseControl(Entity* owner) :
	Component::Component(owner)
{

}

void MouseControl::bindOnMouseButtonActive(MouseButton btn, MButtonAction action) {
	if (m_buttonActiveActions.contains(btn)) {
		m_buttonActiveActions.at(btn).push_back(action);
	}
	else {
		m_buttonActiveActions.insert(std::make_pair(btn, std::vector<MButtonAction>{action}));
	}
}

void MouseControl::bindOnMouseButtonPressed(MouseButton btn, MButtonAction action) {
	if (m_buttonPressedActions.contains(btn)) {
		m_buttonPressedActions.at(btn).push_back(action);
	}
	else {
		m_buttonPressedActions.insert(std::make_pair(btn, std::vector<MButtonAction>{action}));
	}
}

void MouseControl::bindOnMouseButtonReleased(MouseButton btn, MButtonAction action) {
	if (m_buttonReleasedActions.contains(btn)) {
		m_buttonReleasedActions.at(btn).push_back(action);
	}
	else {
		m_buttonReleasedActions.insert(std::make_pair(btn, std::vector<MButtonAction>{action}));
	}
}

const MButtonBindings& MouseControl::getBindingsOnMouseButtonPressed() const {
	return m_buttonPressedActions;
}

const MButtonBindings& MouseControl::getBindingsOnMouseButtonReleased() const {
	return m_buttonReleasedActions;
}

const MButtonBindings& MouseControl::getBindingsOnMouseButtonActive() const {
	return m_buttonActiveActions;
}

} // namespace ba