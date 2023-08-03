#pragma once

#include <unordered_map>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <BA/Inputs/Input.hpp>
#include <BA/Types.hpp>
#include <BA/Utilities/Vector2.hpp>


namespace ba {

// Currently, the max known number of buttons a mouse can have is 15.
enum class MouseButton : std::uint32_t {
	NONE 	=	00,
	LEFT 	=	01,
	MIDDLE	=	02,
	RIGHT 	=	04,
	_4TH 	=	010,
	_5TH 	=	020,
	_6TH 	=	040,
	_7TH 	=	0100,
	_8TH 	=	0200,
	_9TH 	=	0400,
	_10TH 	=	01000,
	_11TH 	=	02000,
	_12TH 	=	04000,
	_13TH 	=	010000,
	_14TH 	=	020000,
	_15TH 	=	040000,
};



class MouseInput : public Input {
public:
	static const IDtype IID;
	
public:
	MouseInput(InputManager* im);

	virtual void handleEvents();

	const Vector2i& getPrevMousePos() const;
	const Vector2i& getCurrMousePos() const;

	bool isButtonUp(MouseButton button) const;
	bool isButtonDown(MouseButton button) const;
	bool isButtonActive(MouseButton button) const;

	float timeSinceLastClicked(MouseButton button) const;
private:
	// Mouse Positions relative to Window
	Vector2i m_prevMousePos{0, 0};
	Vector2i m_currMousePos{0, 0};

	// State of Mouse Buttons
	std::uint32_t 	m_prevMouseButtons = 0u;
	std::uint32_t	m_currMouseButtons = 0u;

	std::unordered_map<ba::uint32, ba::uint64>	m_lastClicked;

public:
	static const float NEVER_CLICKED;
}; // class MouseInput

} // namespace ba