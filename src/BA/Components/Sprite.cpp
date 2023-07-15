#include "BA/Components/Sprite.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

Sprite::Sprite(ba::Entity* owner, IDtype drawLayer, IDtype sortOrder) : 
	Drawable(owner, drawLayer, sortOrder),
	m_textureID(0u) // 0 == no texture
{

}

void Sprite::draw(Window& window) {
	if (m_textureID == 0)
		return;

	SDL_Texture* texture = getOwner()->CONTEXT->resources->getTexture(m_textureID);
	window.draw(texture, m_textureRect, this->getGlobalBounds(), m_owner->getRotation());
	
	// window.drawRect(this->getGlobalBounds(), Color::Blue);
}

bool Sprite::hasTexture() const {
	return m_textureID > 0;
}

IDtype Sprite::loadTextureFromFile(const std::string& fileName) {
	m_textureID = getOwner()->CONTEXT->resources->loadTexture(fileName);

	SDL_Texture* textureObj = getOwner()->CONTEXT->resources->getTexture(m_textureID);

	// Initial textureRect is the whole dimension of the texture.
	m_textureRect.l = 0;
	m_textureRect.t = 0;
	SDL_QueryTexture(textureObj, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

	return m_textureID;
}

void Sprite::setTexture(IDtype textureID) {
	SDL_Texture* textureObj = getOwner()->CONTEXT->resources->getTexture(textureID);
	if(textureObj == nullptr)
		throw std::invalid_argument("Invalid. Non-existent texture ID given,");
	m_textureID = textureID;

	//
	m_textureRect.l = 0;
	m_textureRect.t = 0;
	SDL_QueryTexture(textureObj, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

void Sprite::setTexture(IDtype textureID, const IntRect& rect) {
	SDL_Texture* textureObj = getOwner()->CONTEXT->resources->getTexture(textureID);
	if(textureObj == nullptr)
		throw std::invalid_argument("Invalid. Non-existent texture ID given,");
	m_textureID = textureID;

	m_textureRect = rect;
}

void Sprite::setTextureRect(const IntRect& rect) {
	m_textureRect = rect;
}

IntRect Sprite::getTextureRect() const {
	return m_textureRect;
}

FloatRect Sprite::getLocalBounds() const {
	auto abs = [](float num) -> float {
		return (num >= 0.f) ? num : -num;
	};

	float width = abs(static_cast<float>(m_textureRect.w));
	float height = abs(static_cast<float>(m_textureRect.h));
	return FloatRect({0.f, 0.f}, {width, height});
}

FloatRect Sprite::getGlobalBounds() const {
	return getOwner()->getTransform().transformRect(getLocalBounds());
}

} // namespace ba