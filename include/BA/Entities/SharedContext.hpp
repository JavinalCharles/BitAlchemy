#pragma once

#include "BA/ResourceManager.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class EntityManager;

struct SharedContext {
	ba::EntityManager* 		entities;
	ba::ResourceManager*	resources;
	ba::Window*				window;

}; // struct SharedContext

} // namespace ba