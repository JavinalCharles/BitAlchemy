#pragma once

#include <cmath>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <BA/Entities/SharedContext.hpp>
#include <BA/Scenes/SceneManager.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/Window.hpp>

#include <BA/Tools/DebugHelper.hpp>

namespace ba {

class Engine {
public:
    Engine();
    Engine(const std::string& title, IntRect dimension, std::uint32_t winFlags);

    virtual void init();

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
}; // class Engine

} // namespace ba
