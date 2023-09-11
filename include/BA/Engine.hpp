#pragma once

#include <cmath>
#include <chrono>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <BA/Entities/SharedContext.hpp>
#include <BA/Scenes/SceneManager.hpp>
#include <BA/Scenes/Scene.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/Window.hpp>

#include <BA/Tools/DebugHelper.hpp>

namespace ba {

template <typename S>
concept SceneType = std::is_base_of<Scene, S>::value;

class Engine {
public:
	Engine();
	Engine(const std::string& title, IntRect dimension, std::uint32_t winFlags);

	void setFPSLimit(uint16 fps);
	uint16 getFPSLimit() const;

	virtual void init();

	virtual void onInit();
	virtual void onInit(const std::function<void()>& initFunc);

	template <SceneType T>
	std::shared_ptr<T> createScene();

	IDtype addScene(std::shared_ptr<Scene> scene);

	/***********************************************************************
	 * GAME LOOP METHODS
	************************************************************************/

	/***********************************************************************
	 * @brief Starts the game loop. Only returns when the loop ends.
	 *
	************************************************************************/
	void run();

	void handleEvents();
	void update(float deltaTime);
	void postUpdate(float deltaTime);
	void draw();

	void cleanUp();
protected:
	Window m_window;
	ResourceManager m_resources;

	SceneManager m_sceneManager;

private:


private:
	uint16 m_fpsLimit = 60u;

	std::vector<std::function<void()>> m_initFunctions;
}; // class Engine


/***********************************************************************
 * METHOD IMPLEMENTATIONS
************************************************************************/
template <SceneType T>
std::shared_ptr<T> Engine::createScene() {
	return std::make_shared<T>(&m_window, &m_resources, &m_sceneManager);
}


} // namespace ba
