#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <BA/Globals.hpp>
#include <BA/Utilities/Angle.hpp>
#include <BA/Utilities/Color.hpp>
#include <BA/Utilities/Line.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Window/View.hpp>

namespace ba {

constexpr const int DEFAULT_SCREEN_WIDTH = 640;
constexpr const int DEFAULT_SCREEN_HEIGHT = 480;

constexpr const IDtype DEFAULT_RENDER_LAYER = 0u;
constexpr const IDtype GUI_RENDER_LAYER = 0u - 1; // max value

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
	 */
	void display();



	/**
	 * @brief Handles window specific events.
	 */
	void handleEvents();

	////////////////////////////////////////////////////////////////////////
	// MODIFIERS
	////////////////////////////////////////////////////////////////////////
public:
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
public:
	/**
	 * Instructs the window to use the view mapped to the given renderLayer key. The window will be using this view as target for the draw**() methods, until after this method, or setView() is called again.
	 * @param renderLayer the ID of the view used.
	 * 
	 * @note If RenderLayer does not exists, the window will revert to using DEFAULT_RENDER_LAYER
	 */
	void useViewFromLayer(IDtype renderLayer = DEFAULT_RENDER_LAYER);

	/**
	 * Instructs the Window to use the given view for until this method and useViewFromLayer() has been called.
	 * @param view The View object to be used.
	 */
	void setView(const View& view);

	void setLayerView(IDtype LAYER, const View& newView);



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
	const View& getCurrentView() const;
	View getDefaultView() const;
	FloatRect getViewSpace() const;

	const View& getLayerView(IDtype LAYER = DEFAULT_RENDER_LAYER) const;

	// void setView(const View& view, IDtype RenderLayer = DEFAULT_RENDER_LAYER);

	// void useDefaultView();

private: // Attributes
	std::string 	m_title = "BitAlchemy";
	IntRect 		m_dimension{0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};
	std::uint32_t	m_flags = SDL_WINDOW_SHOWN;

	SDL_Window* 	m_window = nullptr;

	// View			m_defaultView{{0.f, 0.f, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT}};
	// View 			m_view{{0.f, 0.f, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT}};

	std::map<IDtype, View> m_views{{DEFAULT_RENDER_LAYER, View(m_dimension)}};
	View m_currentView = m_views.at(DEFAULT_RENDER_LAYER);

	bool 			m_open = false;
}; // class Window

} // namespace ba
