#pragma once

#include <BA/Inputs/InputManager.hpp>
#include <BA/Resources/Warehouse.hpp>
#include <BA/Systems/MusicPlayer.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class EntityManager;

using ba::Resources::Warehouse;

struct SharedContext {
	EntityManager* 		entities 	= nullptr;
	Warehouse*			warehouse 	= nullptr;
	Window*				window 		= nullptr;
	InputManager*		inputs 		= nullptr;
	MusicPlayer*		player 		= nullptr;
}; // struct SharedContext

} // namespace ba