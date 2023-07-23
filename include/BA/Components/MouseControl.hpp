#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "BA/Components/Component.hpp"
#include "BA/Inputs/InputManager.hpp"
#include "BA/Inputs/MouseInput.hpp"

namespace ba {

using MButtonAction = std::function<void(void)>;
using MButtonBindings = std::unordered_map<ba::MouseButton, std::vector<MButtonAction>>;

class MouseControl : public Component {
public:
	MouseControl(Entity* owner);

	void bindOnMouseButtonActive(MouseButton btn, MButtonAction action);
	void bindOnMouseButtonReleased(MouseButton btn, MButtonAction action);
	void bindOnMouseButtonPressed(MouseButton btn, MButtonAction action);

	const MButtonBindings& getBindingsOnMouseButtonPressed() const;
	const MButtonBindings& getBindingsOnMouseButtonReleased() const;
	const MButtonBindings& getBindingsOnMouseButtonActive() const;
private:
	MButtonBindings		m_buttonPressedActions;
	MButtonBindings		m_buttonActiveActions;
	MButtonBindings		m_buttonReleasedActions;
public:
	static const IDtype CID;

}; // class MouseButton


} // namespace ba