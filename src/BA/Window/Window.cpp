#include "BA/Window/Window.hpp"
#ifdef DEBUG_MODE_ON
#include <iostream>
#endif

namespace ba {

Window::Window(const std::string& title, int x, int y, int w, int h, std::uint32_t baags) :
	m_defaultView({
		0.f, 0.f, 
		static_cast<float>(w), 
		static_cast<float>(h)}),
	m_view(m_defaultView)
{
	m_window = SDL_CreateWindow(title.c_str(), x, y, w, h, baags);
	if (m_window == NULL) {
		throw std::runtime_error(SDL_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL) {
		throw std::runtime_error(SDL_GetError());
	}

	m_open = true;
}


bool Window::isOpen() const {
	return m_open;
}

void Window::close() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_open = false;
	m_renderer = NULL;
	m_window = NULL;
}

void Window::handleEvents() {
	SDL_Event e[1];
	while(SDL_PeepEvents(e, 1, SDL_GETEVENT, SDL_WINDOWEVENT, SDL_WINDOWEVENT) > 0) {
		switch(e[0].window.event) {
			case SDL_WINDOWEVENT_FOCUS_LOST:
				// Pause the game
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				// Resume the game
				break;
			case SDL_WINDOWEVENT_CLOSE:
				this->close();
				return; // Terminate function. No need to handle other events.
		}
	}

	if(SDL_PeepEvents(e, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT) > 0) {
		this->close();
	}
}

void Window::clear(ba::Color color) {
	SDL_SetRenderDrawColor( m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);
}

void Window::draw(SDL_Texture* texture, const ba::IntRect& textureRect, const FloatRect& destRect) {

	SDL_Rect screenCoordsRect = m_view.mapToView(destRect).toSDL_Rect();
	SDL_Rect textureSDLRect = textureRect.toSDL_Rect();

	#ifdef DEBUG_MODE_ON
	#ifdef DEBUG_VERBOSE_ENABLED
	std::cout << "Rendering to screen: " << screenCoordsRect.x << ", " << screenCoordsRect.y << ";" << std::endl;
	#endif
	#endif

	SDL_RenderCopy(m_renderer, texture, &textureSDLRect, &screenCoordsRect);
}

void Window::display() {
	SDL_RenderPresent(m_renderer);
}

SDL_Window* Window::getWindow() const {
	return m_window;
}

Vector2i Window::getSize() const {
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(m_window, &w, &h);

	return Vector2i{w, h};
}

SDL_Renderer* Window::getRenderer() const {
	return m_renderer;
}

const View& Window::getDefaultView() const {
	return m_defaultView;
}

const View& Window::getView() const {
	return m_view;
}

void Window::setView(const View& view) {
	m_view = view;
}

FloatRect Window::getViewSpace() const {
	return m_view.getViewSpace();
}

} // namespace ba