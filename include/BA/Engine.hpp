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
#include <BA/Exceptions/Inaccessible.hpp>
#include <BA/Scenes/SceneManager.hpp>
#include <BA/Scenes/Scene.hpp>
#include <BA/Systems/EntityManager.hpp>
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
	Engine(const std::string& orgName, const std::string& appName);
	Engine(const std::string& orgName, const std::string& appName, const std::string& configFileName);
	Engine(const std::string& orgName, const std::string& appName, const IntRect& windowDimension, ba::uint32 windowFlags);
	Engine(const std::string& title, const IntRect& dimension, ba::uint32 winFlags);

	Engine(Engine& other) = delete;
	Engine& operator=(Engine& other) = delete;

	//////////////////////////////////////////////////////////////////////////
	// SYSTEMS CONFIGURATION
	/////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// GAME CONFIGURATION
	//////////////////////////////////////////////////////////////////////////
	void setFPSLimit(uint16 fps);

	Window& getWindow();
	ResourceManager& getResourceManager();

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
	void init();

	/**
	 * @brief Starts the game loop. Only returns when the loop ends.
	**/
	void run();

	void handleEvents();
	void update(float deltaTime);
	void postUpdate(float deltaTime);
	void draw();

	void cleanUp();

private:
	void __construct(const std::string& org = "", const std::string& appName = "");

protected:
	Window m_window;
	ResourceManager m_resources;

	SceneManager m_sceneManager;

private:
	uint16 m_fpsLimit = 60u;

	std::vector<std::function<void()>> m_initFunctions;
}; // class Engine


/**
 * METHOD IMPLEMENTATIONS
**/
template <SceneType T>
std::shared_ptr<T> Engine::createScene() {
	return std::make_shared<T>(&m_window, &m_resources, &m_sceneManager);
}


} // namespace ba
