#include "BA/Window/Window.hpp"
#ifdef DEBUG_MODE_ON
#include <iostream>
#endif

namespace ba {

Window::Window() {
	auto iter = m_views.insert_or_assign(DEFAULT_RENDER_LAYER, View(m_dimension));
	setView(iter.first->second);
}

Window::Window(const std::string& title, const ba::IntRect& dimension, ba::uint32 flags) :
	m_title(title),
	m_dimension(dimension),
	m_flags(flags),
	m_views(),
	m_currentView()
{
	auto iter = m_views.insert_or_assign(DEFAULT_RENDER_LAYER, View(m_dimension));
	setView(iter.first->second);
}


Window::Window(const std::string& title, int x, int y, int w, int h, ba::uint32 flags) :
	m_title(title),
	m_dimension(x, y, w, h),
	m_flags(flags),
	m_views(),
	m_currentView()
{
	auto iter = m_views.insert_or_assign(DEFAULT_RENDER_LAYER, View(m_dimension));
	setView(iter.first->second);
}

Window::~Window() {
	if (globalRenderer != nullptr) {
		SDL_DestroyRenderer(globalRenderer);
	}
	globalRenderer = nullptr;
	if (m_window != nullptr) {
		SDL_DestroyWindow(m_window);
	}
	m_window = nullptr;
	m_open = false;
}

void Window::setFlags(uint32 flags) {
	m_flags = flags;
}

void Window::addFlags(uint32 flags) {
	m_flags |= flags;
}

void Window::setSize(const Vector2i& newSize) {
	m_dimension.w = newSize.x;
	m_dimension.h = newSize.y;
}

void Window::setSize(int w, int h) {
	m_dimension.w = w;
	m_dimension.h = h;
}

void Window::setDimension(int x, int y, int w, int h) {
	m_dimension.t = x;
	m_dimension.l = y;
	m_dimension.w = w;
	m_dimension.h = h;
}

void Window::setDimension(const Vector2i& pos, const Vector2i& size) {
	m_dimension.setPosition(pos);
	m_dimension.setArea(size);
}

void Window::setDimension(const IntRect& newDimension) {
	m_dimension = newDimension;
}

void Window::useViewFromLayer(IDtype renderLayer) {
	if (!m_views.contains(renderLayer)) {
		renderLayer = DEFAULT_RENDER_LAYER;
	}
	setView(m_views.at(renderLayer));
}

void Window::setView(const View& view) {
	m_currentView = view;
	SDL_Rect rect = m_currentView.getViewport().toSDL_Rect();
	int err = SDL_RenderSetViewport(globalRenderer, &rect);
}

void Window::setLayerView(IDtype LAYER, const View& newView) {
	m_views.insert_or_assign(LAYER, newView);
}


void Window::init() {
	m_window = SDL_CreateWindow(m_title.c_str(), m_dimension.l, m_dimension.t, m_dimension.w, m_dimension.h, m_flags);
	if (m_window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	if (globalRenderer == nullptr) {
		globalRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (globalRenderer == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
	}

	

	m_open = true;
}


bool Window::isOpen() const {
	return m_open;
}

void Window::close() {
	/**
	 * TODO: Take into account the possibility of a game having multiple
	 * windows, and thus provide a means of tracking number of windows
	 * and only destroy the globalRenderer upon the closing of the 
	 * LAST window.
	 * 
	 */
	SDL_DestroyRenderer(globalRenderer);
	SDL_DestroyWindow(m_window);
	m_open = false;
	m_window = nullptr;
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
	SDL_SetRenderDrawColor(globalRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(globalRenderer);
}

void Window::display() {
	SDL_RenderPresent(globalRenderer);
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
	SDL_Rect screenDest = m_currentView.mapToView(destRect).toSDL_Rect();

	SDL_RenderCopy(globalRenderer, texture, NULL, &screenDest);
}

void Window::draw(SDL_Texture* texture, const ba::IntRect& textureRect, const FloatRect& destRect, const Angle& angle) {
	SDL_RendererFlip flip = getFlip(textureRect);

	SDL_Rect screenCoordsRect = m_currentView.mapToView(destRect).toSDL_Rect();
	SDL_Rect textureSDLRect = textureRect.toSDL_Rect();

	SDL_RenderCopyEx(globalRenderer, texture, &textureSDLRect, &screenCoordsRect, angle.asDegrees(), NULL, flip);
}

void Window::drawPoint(const Vector2f& point, const Color& pc) {
	Color cb; // Color buffer
	Vector2f sc = m_currentView.mapToView(point);
	SDL_Point points[] = {
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x)+1, static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x)-1, static_cast<int>(sc.y)},
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)+1},
		SDL_Point{static_cast<int>(sc.x), 	static_cast<int>(sc.y)-1}
	};

	SDL_GetRenderDrawColor(globalRenderer, &cb.r, &cb.g, &cb.b, &cb.a);

	SDL_SetRenderDrawColor(globalRenderer, pc.r, pc.g, pc.b, pc.a);
	SDL_RenderDrawPoint(globalRenderer, sc.x, sc.y);
	SDL_RenderDrawPoints(globalRenderer, points, 5);


	SDL_SetRenderDrawColor(globalRenderer, cb.r, cb.g, cb.b, cb.a);
}

void Window::drawLine(const IntLine& l, const Color& lc) {
	Color cb;
	SDL_GetRenderDrawColor(globalRenderer, &cb.r, &cb.g, &cb.b, &cb.a);
	SDL_SetRenderDrawColor(globalRenderer, lc.r, lc.g, lc.b, lc.a);
	Vector2i p1 = m_currentView.mapToView(l.p1);
	Vector2i p2 = m_currentView.mapToView(l.p2);

	SDL_RenderDrawLine(globalRenderer, p1.x, p1.y, p2.x, p2.y);

	SDL_SetRenderDrawColor(globalRenderer, cb.r, cb.g, cb.b, cb.a);
}

void Window::drawRect(const IntRect& rect, const Color& rc) {
	Color cb; // Color Buffer
	SDL_Rect r = m_currentView.mapToView(rect).toSDL_Rect();
	SDL_GetRenderDrawColor(globalRenderer, &cb.r, &cb.g, &cb.b, &cb.a);
	SDL_SetRenderDrawColor(globalRenderer, rc.r, rc.g, rc.b, rc.a);
	SDL_RenderDrawRect(globalRenderer, &r);
	SDL_SetRenderDrawColor(globalRenderer, cb.r, cb.g, cb.b, cb.a);
}

void Window::drawOnScreen(SDL_Texture* texture, const FloatRect& destRect) {
	SDL_Rect screenDest = destRect.toSDL_Rect();

	SDL_RenderCopy(globalRenderer, texture, NULL, &screenDest);
}

void Window::drawOnScreen(SDL_Texture* texture, const IntRect& textureRect, const FloatRect& destRect, const Angle& angle) {
	SDL_RendererFlip flip = getFlip(textureRect);

	SDL_Rect screenCoordsRect = destRect.toSDL_Rect();
	SDL_Rect textureSDLRect = textureRect.toSDL_Rect();

	SDL_RenderCopyEx(globalRenderer, texture, &textureSDLRect, &screenCoordsRect, angle.asDegrees(), NULL, flip);
}

void Window::drawPointOnScreen(const Vector2f& p, Color pc) {
	Color cb;
	SDL_Point points[] = {
		SDL_Point{static_cast<int>(p.x), 	static_cast<int>(p.y)},
		SDL_Point{static_cast<int>(p.x)+1, static_cast<int>(p.y)},
		SDL_Point{static_cast<int>(p.x)-1, static_cast<int>(p.y)},
		SDL_Point{static_cast<int>(p.x), 	static_cast<int>(p.y)+1},
		SDL_Point{static_cast<int>(p.x), 	static_cast<int>(p.y)-1}
	};

	SDL_GetRenderDrawColor(globalRenderer, &cb.r, &cb.g, &cb.b, &cb.a);

	SDL_SetRenderDrawColor(globalRenderer, pc.r, pc.g, pc.b, pc.a);
	SDL_RenderDrawPoint(globalRenderer, p.x, p.y);
	SDL_RenderDrawPoints(globalRenderer, points, 5);


	SDL_SetRenderDrawColor(globalRenderer, cb.r, cb.g, cb.b, cb.a);
}

void Window::drawRectOnScreen(const IntRect& rect, Color rc) {
	Color cb;
	SDL_Rect r = rect.toSDL_Rect();
	SDL_GetRenderDrawColor(globalRenderer, &cb.r, &cb.g, &cb.b, &cb.a);
	SDL_SetRenderDrawColor(globalRenderer, rc.r, rc.g, rc.b, rc.a);
	SDL_RenderDrawRect(globalRenderer, &r);
	SDL_SetRenderDrawColor(globalRenderer, cb.r, cb.g, cb.b, cb.a);
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
	return globalRenderer;
}

View Window::getDefaultView() const {
// 	return m_defaultView;
	return View(m_dimension);
}

const View& Window::getCurrentView() const {
	return m_currentView;
}

const View& Window::getLayerView(IDtype LAYER) const {
	if (!m_views.contains(LAYER)) {
		LAYER = DEFAULT_RENDER_LAYER;
	}
	return m_views.at(LAYER);
}

// void Window::setView(const View& view) {
// 	m_view = view;
// 	SDL_Rect rect = m_view.getViewport().toSDL_Rect();
// 	SDL_RenderSetViewport(globalRenderer, &rect);
// }

// void Window::useDefaultView() {
// 	m_view = m_defaultView;
// 	SDL_RenderSetViewport(globalRenderer, nullptr);
// }

FloatRect Window::getViewSpace() const {
	return m_currentView.getViewSpace();
}

} // namespace ba
