#pragma once

#include <BA/Inputs/InputManager.hpp>
#include <BA/Systems/MusicPlayer.hpp>
#include "BA/ResourceManager.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class EntityManager;

struct SharedContext {
	EntityManager* 		entities 	= nullptr;
	ResourceManager*	resources 	= nullptr;
	Window*				window 		= nullptr;
	InputManager*		inputs 		= nullptr;
	MusicPlayer*		player 		= nullptr;
}; // struct SharedContext

} // namespace ba