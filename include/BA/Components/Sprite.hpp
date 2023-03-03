#pragma once

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <BA/Components/Drawable.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

class Sprite : public ba::Drawable {
public:
	Sprite(ba::Entity* owner, unsigned drawLayer = 0, unsigned sortOrder = 0);

	virtual void draw(ba::Window& window);

	unsigned loadTextureFromFile(const std::string& path);
	void setTextureRect(const IntRect& rect);
	IntRect getTextureRect() const;

	FloatRect getLocalBounds() const;
	virtual FloatRect getGlobalBounds() const;

private:
	unsigned m_textureID;

	ba::IntRect m_textureRect;
}; // class Sprite

}; // namespace ba