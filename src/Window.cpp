#include "BA/Window/Window.hpp"

using ba::Window;

Window::Window()
	: m_title(),
	m)pos(),
	m_width(),
	m_height(),
	m_flags(),
	m_window(nullptr),
	m_renderer(nullptr)
{

}

Window::Window(const std::string& title, int x, int y, int w, int h, uint32 flags)
	: m_title(title),
	m)pos(x, y),
	m_width(w),
	m_height(h),
	m_flags(flags),
	m_window(nullptr),
	m_renderer(nullptr)
{
	createWindow();
}

void Window::createWindow() {
	m_window = SDL_CreateWindow(m_title.c_str(), m_pos.x, m_pos.y, m_width, m_height, m_flags);
}

void Window::setTitle(const std::string& title) {
	m_title = title;
}

void Window::setPos(int x, int y) {
	m_pos.x = x;
	m_pos.y = y;
}

void Window::setPos(const ba::Point2i& pos) {
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void Window::setWidth(int width) {
	m_width = width;
}

void Window::setHeight(int height) {
	m_height = height;
}

void Window::setFlags(uint32 flags) {
	m_flags = flags;
}

void Window::addFlags(uint32 flags) {
	m_flags |= flags;
}