#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Types.hpp"
#include "BA/Systems/Vector2.hpp"

namespace ba {
	const int DEFAULT_SCREEN_WIDTH = 640;
	const int DEFAULT_SCREEN_HEIGHT = 480;



class Window {
public:
	// Window Flags
	static const uint32 FULLSCREEN = SDL_WINDOW_FULLSCREEN;
	static const uint32 OPENGL = SDL_WINDOW_OPENGL;
	static const uint32 VULKAN = SDL_WINDOW_VULKAN;
	static const uint32 METAL = SDL_WINDOW_METAL;
	static const uint32 FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP;
	static const uint32 HIDDEN = SDL_WINDOW_HIDDEN;
	static const uint32 SHOWN = SDL_WINDOW_SHOWN;
	static const uint32 BORDERLESS = SDL_WINDOW_BORDERLESS;
	static const uint32 RESIZABLE = SDL_WINDOW_RESIZABLE;
	static const uint32 MINIMIZED = SDL_WINDOW_MINIMIZED;
	static const uint32 MAXIMIZED = SDL_WINDOW_MAXIMIZED;
	static const uint32 INPUT_GRAB = SDL_WINDOW_INPUT_GRABBED;
	static const uint32 ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI;
	

public:
	/**
	 * Base constructor. starts the underlying 
	 * window object as NULL.
	 * Use the set methods to set the attributes then
	 * call createWindow to create an actual window.
	*/
	explicit Window();

	/**
	 * Window Constructor with attributes. Calls the
	 * createWindow() method after setting all the
	 * attributes.
	*/
	Window(const std::string& title, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int w = DEFAULT_SCREEN_WIDTH, int h = DEFAULT_SCREEN_HEIGHT, uint32 flags = Window::SHOWN);

public:
	void createWindow();

	void setTitle(const std::string& title);
	void setPos(int x, int y);
	void setPos(const ba::Vector2i& pos);
	void setWidth(int width);
	void setHeight(int height);
	void setFlags(uint32 flags);
	
	void addFlags(uint32 flags);

private:
	std::string		m_title;
	ba::Vector2i	m_pos;
	int				m_width;
	int				m_height;
	uint32 			m_flags;


	SDL_Window* 	m_window;
	SDL_Renderer* 	m_renderer;
}; // class Window

} // namespace ba

