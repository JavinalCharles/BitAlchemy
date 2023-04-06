#pragma once

#include <BA/Systems/InputManager.hpp>
#include <BA/Systems/MusicPlayer.hpp>
#include "BA/ResourceManager.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class EntityManager;

struct SharedContext {
	EntityManager* 		entities;
	ResourceManager*	resources;
	Window*				window;
	InputManager*		inputs;
	MusicPlayer*		player;
}; // struct SharedContext

} // namespace ba