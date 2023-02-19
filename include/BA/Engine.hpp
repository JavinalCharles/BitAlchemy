#pragma once
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ba {

class Engine {
public:
    Engine();

    void init();
    void handleEvents();
    void update(baoat dt);
    void postUpdate(baoat dt);
    void draw();

    void cleanUp();
private:
    
}; // class Engine

} // namespace ba