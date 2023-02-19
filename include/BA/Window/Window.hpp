#pragma once

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "BA/Utilities/Color.hpp"
#include "BA/Utilities/Rect.hpp"

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;

namespace ba {
class Window {
public:
	Window(const std::string& title, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int w = DEFAULT_SCREEN_WIDTH, int h = DEFAULT_SCREEN_HEIGHT, std::uint32_t baags = SDL_WINDOW_SHOWN);

	bool isOpen() const;
	void close();

	// TODO: OTHER METHODS
	void clear(ba::Color color = ba::Color::Black);

	void draw(SDL_Texture* texture, const ba::IntRect& srcRect, const ba::IntRect& destRect);
	void draw(SDL_Texture* texture, const ba::IntRect& destRect);

	void display();

	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;

private: // Attributes
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_open;
}; // class Window

} // namespace ba