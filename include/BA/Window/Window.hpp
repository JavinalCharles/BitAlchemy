#pragma once

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <BA/Utilities/Angle.hpp>
#include <BA/Utilities/Color.hpp>
#include <BA/Utilities/Line.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/View.hpp>

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;

namespace ba {
class Window {
public:
	Window();
	Window(const std::string& title, int x, int y, int w, int h, std::uint32_t flags);

	void init();

	bool isOpen() const;
	void close();

	/**
	 * @brief Allows the window to handle window specific events.
	*/
	void handleEvents();

	void clear(ba::Color color = ba::Color::Black);

	void draw(SDL_Texture* texture, const FloatRect& destRect);
	void draw(SDL_Texture* texture, const IntRect& textureRect, const FloatRect& destRect, const Angle& angle = Angle::Zero);
	void drawPoint(const Vector2f& point, const Color& pointColor = Color::White);
	void drawLine(const IntLine& line, const Color& lineColor = Color::White);
	void drawRect(const IntRect& rect, const Color& rectColor = Color::White);

	void drawOnScreen(SDL_Texture* texture, const FloatRect& destRect);
	void drawOnScreen(SDL_Texture* texture, const IntRect& textureRect, const FloatRect& destRect, const Angle& angle = Angle::Zero);
	void drawPointOnScreen(const Vector2f& point, Color pointColor = Color::White);
	void drawRectOnScreen(const IntRect& rect, Color rectColor = Color::White);


	void display();

	SDL_Window* getWindow() const;
	Vector2i getSize() const;
	SDL_Renderer* getRenderer() const;
	const View& getView() const;
	const View& getDefaultView() const;
	FloatRect getViewSpace() const;

	void setView(const View& view);

private: // Attributes
	std::string 	m_title = "BitAlchemy";
	IntRect 		m_dimension{0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};
	std::uint32_t	m_flags = SDL_WINDOW_SHOWN;

	SDL_Window* 	m_window = nullptr;
	SDL_Renderer* 	m_renderer = nullptr;

	View			m_defaultView{{0.f, 0.f, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT}};
	View 			m_view{{0.f, 0.f, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT}};

	bool 			m_open{false};
}; // class Window

} // namespace ba
