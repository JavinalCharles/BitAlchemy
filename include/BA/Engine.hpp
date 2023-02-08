#pragma once
#include <SDL2/SDL.h>

namespace ba {
    class Engine {
    public:
        Engine();

        void init();
        void handleEvents();
        void update(float dt);
        void postUpdate(float dt);
        void draw();

        void cleanUp();
    private:
        
    };
}