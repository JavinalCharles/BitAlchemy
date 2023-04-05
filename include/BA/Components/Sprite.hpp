#pragma once

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <BA/Components/Boundable.hpp>
#include <BA/Components/Drawable.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

class Sprite : public Drawable, Boundable {
public:
	Sprite(ba::Entity* owner, unsigned drawLayer = 0, unsigned sortOrder = 0);

	virtual void draw(ba::Window& window);

	unsigned loadTextureFromFile(const std::string& path);
	void setTextureRect(const IntRect& rect);
	IntRect getTextureRect() const;

	virtual FloatRect getLocalBounds() const override;
	virtual FloatRect getGlobalBounds() const override;

private:
	unsigned m_textureID;

	ba::IntRect m_textureRect;
}; // class Sprite

}; // namespace ba