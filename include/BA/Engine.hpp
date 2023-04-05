#pragma once

#include <cmath>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <BA/Entities/SharedContext.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/Window.hpp>

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

    SharedContext* getContext();

    void cleanUp();
protected:
    Window m_window;
    EntityManager m_entities;
    ResourceManager m_resources;
    InputManager m_inputs;

    SharedContext m_context;

}; // class Engine

} // namespace ba