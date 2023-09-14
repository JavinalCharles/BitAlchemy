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
#include <BA/Tools/ConfigLoader.hpp>
#include <BA/Tools/DebugHelper.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/Window.hpp>



namespace ba {

template <typename S>
concept SceneType = std::is_base_of<Scene, S>::value;

class Engine {
public:
	Engine();
	Engine(const std::string& organization, const std::string& title, const IntRect& windowDimension, ba::uint32 windowFlags);
	Engine(const std::string& title, const IntRect& dimension, ba::uint32 winFlags);

	Engine(Engine& other) = delete;
	Engine& operator=(Engine& other) = delete;

	//////////////////////////////////////////////////////////////////////////
	// ENGINE CONFIGURATION
	//////////////////////////////////////////////////////////////////////////
	void setFPSLimit(uint16 fps);

	void setWindowSize(int width, int height);
	void setWindowSize(const Vector2i& windowArea);
	void setWindowDimension(int x, int y, int w, int h);
	void setWindowDimension(const Vector2i& pos, const Vector2i& size);
	void setWindowDimension(const IntRect& dimension);

	void setWindowFlags(uint32 flags);
	void addWindowFlags(uint32 flags);

	virtual void onInit();
	virtual void onInit(const std::function<void()>& initFunc);

	template <SceneType T>
	std::shared_ptr<T> createScene();

	IDtype addScene(std::shared_ptr<Scene> scene);

	///////////////////////////////////////////////////////////////////////////
	// ENGINE DATA EXTRACTION
	///////////////////////////////////////////////////////////////////////////
	uint16 getFPSLimit() const;

	///////////////////////////////////////////////////////////////////////////
	// GAME LOOP METHODS
	///////////////////////////////////////////////////////////////////////////

	/***********************************************************************
	 * @brief Starts the game loop. Only returns when the loop ends.
	************************************************************************/
	void init();

	void run();

	void handleEvents();
	void update(float deltaTime);
	void postUpdate(float deltaTime);
	void draw();

	void cleanUp();
private:
	void loadConfig();

protected:
	Window m_window;
	ResourceManager m_resources;

	SceneManager m_sceneManager;

private:
	ConfigMap m_configs;

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
