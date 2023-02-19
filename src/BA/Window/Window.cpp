#include "BA/Window/Window.hpp"

namespace ba {

Window::Window(const std::string& title, int x, int y, int w, int h, std::uint32_t baags) {
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

void Window::clear(ba::Color color) {
	SDL_SetRenderDrawColor( m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);
}

void Window::draw(SDL_Texture* texture, const ba::IntRect& srcRect, const ba::IntRect& destRect) {
	SDL_Rect srcSDLRect = srcRect.toSDL_Rect();
	SDL_Rect dstSDLRect = destRect.toSDL_Rect();
	SDL_RenderCopy(m_renderer, texture, &srcSDLRect, &dstSDLRect);
}

void Window::draw(SDL_Texture* texture, const ba::IntRect& destRect) {
	SDL_Rect dstSDLRect = destRect.toSDL_Rect();
	SDL_RenderCopy(m_renderer, texture, NULL ,&dstSDLRect);
}

void Window::display() {
	SDL_RenderPresent(m_renderer);
}

SDL_Window* Window::getWindow() const {
	return m_window;
}

SDL_Renderer* Window::getRenderer() const {
	return m_renderer;
}

} // namespace ba