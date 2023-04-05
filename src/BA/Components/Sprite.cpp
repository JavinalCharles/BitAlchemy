#include "BA/Components/Sprite.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

Sprite::Sprite(ba::Entity* owner, unsigned drawLayer, unsigned sortOrder) : 
	Drawable(owner, drawLayer, sortOrder),
	m_textureID(0u) // 0 == no texture
{

}

void Sprite::draw(Window& window) {
	if (m_textureID == 0)
		return;

	SDL_Texture* texture = getOwner()->CONTEXT->resources->getTexture(m_textureID);
	window.draw(texture, m_textureRect, this->getGlobalBounds());
	window.drawRect(this->getGlobalBounds(), Color::Blue);
}

unsigned Sprite::loadTextureFromFile(const std::string& path) {
	m_textureID = getOwner()->CONTEXT->resources->loadTexture(path);

	SDL_Texture* textureObj = getOwner()->CONTEXT->resources->getTexture(m_textureID);

	int width = 0;
	int height = 0;
	SDL_QueryTexture(textureObj, NULL, NULL, &width, &height);
	// Initial textureRect becomes {0, 0, width, height}; ie. The whole size of the texture.
	m_textureRect.w = width;
	m_textureRect.h = height;

	return m_textureID;
}

void Sprite::setTextureRect(const IntRect& rect) {
	m_textureRect = rect;
}

IntRect Sprite::getTextureRect() const {
	return m_textureRect;
}

FloatRect Sprite::getLocalBounds() const {
	float width = static_cast<float>(m_textureRect.w);
	float height = static_cast<float>(m_textureRect.h);
	return FloatRect({0.f, 0.f}, {width, height});
}

FloatRect Sprite::getGlobalBounds() const {
	return getOwner()->getTransform().transformRect(getLocalBounds());
}

} // namespace ba