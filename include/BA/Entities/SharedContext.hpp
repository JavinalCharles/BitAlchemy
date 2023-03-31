#pragma once

#include <BA/Systems/InputManager.hpp>
#include "BA/ResourceManager.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class EntityManager;

struct SharedContext {
	EntityManager* 		entities;
	ResourceManager*	resources;
	Window*				window;
	InputManager*		inputs;
}; // struct SharedContext

} // namespace ba