#include "BA/Window/Window.hpp"
#ifdef DEBUG_MODE_ON
#include <iostream>
#endif

namespace ba {

Window::Window() = default;

Window::Window(const std::string& title, int x, int y, int w, int h, std::uint32_t flags) :
	m_title(title),
	m_dimension(x, y, w, h),
	m_flags(flags),
	m_defaultView({
		0.f, 0.f, 
		static_cast<float>(w), 
		static_cast<float>(h)}),
	m_view(m_defaultView)
{
	
}

void Window::init() {
	m_window = SDL_CreateWindow(m_title.c_str(), m_dimension.l, m_dimension.t, m_dimension.w, m_dimension.h, m_flags);
	if (m_window == nullptr) {
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

namespace {
	SDL_RendererFlip getFlip(const IntRect& rect) {
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if(rect.w < 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if(rect.h < 0) {
			flip = SDL_FLIP_VERTICAL;
		}
		return flip;
	}
} // anonymous namespace

void Window::draw(SDL_Texture* texture, const FloatRect& destRect) {
	SDL_Rect screenDest = m_view.mapToView(destRect).toSDL_Rect();

	SDL_RenderCopy(m_renderer, texture, NULL, &screenDest);
}

void Window::draw(SDL_Texture* texture, const ba::IntRect& textureRect, const FloatRect& destRect, const Angle& angle) {
	SDL_RendererFlip flip = getFlip(textureRect);

	SDL_Rect screenCoordsRect = m_view.mapToView(destRect).toSDL_Rect();
	SDL_Rect textureSDLRect = textureRect.toSDL_Rect();

	SDL_RenderCopyEx(m_renderer, texture, &textureSDLRect, &screenCoordsRect, angle.asDegrees(), NULL, flip);
}

void Window::drawPoint(const Vector2f& point, Color pc) {
	Color cb; // Color buffer
	Vector2f sc = m_view.mapToView(point);
	SDL_Point points[] = {
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x)+1, static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x)-1, static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)+1},
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)-1}
	};

	SDL_GetRenderDrawColor(m_renderer, &cb.r, &cb.g, &cb.b, &cb.a);

	SDL_SetRenderDrawColor(m_renderer, pc.r, pc.g, pc.b, pc.a);
	SDL_RenderDrawPoint(m_renderer, sc.x, sc.y);
	SDL_RenderDrawPoints(m_renderer, points, 5);


	SDL_SetRenderDrawColor(m_renderer, cb.r, cb.g, cb.b, cb.a);
}

void Window::drawRect(const IntRect& rect, Color rc) {
	Color cb; // Color Buffer
	SDL_Rect r = m_view.mapToView(rect).toSDL_Rect();
	SDL_GetRenderDrawColor(m_renderer, &cb.r, &cb.g, &cb.b, &cb.a);
	SDL_SetRenderDrawColor(m_renderer, rc.r, rc.g, rc.b, rc.a);
	SDL_RenderDrawRect(m_renderer, &r);
	SDL_SetRenderDrawColor(m_renderer, cb.r, cb.g, cb.b, cb.a);
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