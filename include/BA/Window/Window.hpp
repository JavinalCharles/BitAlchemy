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
	////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS and DESTRUCTORS
	////////////////////////////////////////////////////////////////////////
	Window();

	Window(const std::string& title, const IntRect& dimension, ba::uint32 flags = SDL_WINDOW_SHOWN);
	Window(const std::string& title, int x, int y, int w, int h, ba::uint32 flags = SDL_WINDOW_SHOWN);
	~Window();

	Window(Window& other) = delete;
	Window& operator=(Window& window) = delete;

	////////////////////////////////////////////////////////////////////////
	// LOOP METHODS
	////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Initializes the window with the flags and states set by the
	 * user through Window::set*() methods.
	**/
	void init();

	/**
	 * @brief Checks if the window is still open.
	 *
	 * @return true if the window is still open, otherwise false.
	**/
	bool isOpen() const;

	/**
	 * @brief Closes the window and deallocates memory used for its
	 * initialization and usage.
	**/
	void close();

	/**
	 * @brief fills the window's content with the specified color.
	 *
	 * @param color the color to fill the canvas with.
	**/
	void clear(ba::Color color = ba::Color::Black);

	/**
	 * @brief Displays on window's content the textures/objects given to the
	 * various Window::draw*() methods.
	**/
	void display();



	/**
	 * @brief Handles window specific events.
	**/
	void handleEvents();

	////////////////////////////////////////////////////////////////////////
	// MODIFIERS
	////////////////////////////////////////////////////////////////////////
	void setFlags(uint32 flags);
	void addFlags(uint32 flags);

	void setSize(const Vector2i& newSize);
	void setSize(int w, int h);

	void setDimension(int x, int y, int w, int h);
	void setDimension(const Vector2i& pos, const Vector2i& size);
	void setDimension(const IntRect& newDimension);

	////////////////////////////////////////////////////////////////////////
	// MODIFIERS
	////////////////////////////////////////////////////////////////////////






	///////////////////////////////////////////////////////////////////////////
	// DRAWING METHODS
	///////////////////////////////////////////////////////////////////////////
	void draw(SDL_Texture* texture, const FloatRect& destRect);
	void draw(SDL_Texture* texture, const IntRect& textureRect, const FloatRect& destRect, const Angle& angle = Angle::Zero);
	void drawPoint(const Vector2f& point, const Color& pointColor = Color::White);
	void drawLine(const IntLine& line, const Color& lineColor = Color::White);
	void drawRect(const IntRect& rect, const Color& rectColor = Color::White);

	void drawOnScreen(SDL_Texture* texture, const FloatRect& destRect);
	void drawOnScreen(SDL_Texture* texture, const IntRect& textureRect, const FloatRect& destRect, const Angle& angle = Angle::Zero);
	void drawPointOnScreen(const Vector2f& point, Color pointColor = Color::White);
	void drawRectOnScreen(const IntRect& rect, Color rectColor = Color::White);




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
