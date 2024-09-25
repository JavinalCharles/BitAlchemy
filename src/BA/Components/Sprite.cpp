#include "BA/Components/Sprite.hpp"
#include "BA/Entities/Entity.hpp"

namespace ba {

using ba::Resources::TextureManager;
namespace fs = std::filesystem;

Sprite::Sprite(ba::Entity* owner, IDtype drawLayer) :
	Drawable(owner, drawLayer),
	m_textureID(0u) // 0 == no texture
{

}

void Sprite::draw(Window& window) {
	if (m_textureID != 0) {
		SDL_Texture* texture = getOwner()->CONTEXT->warehouse->getManager<ba::Resources::TextureManager>().at(m_textureID).get();
		window.draw(texture, m_textureRect, this->getGlobalBounds(), m_owner->getRotation());
	}

	// window.drawRect(this->getGlobalBounds(), Color::Yellow);

	// auto collider = getOwner()->getCollider();
	// if (collider != nullptr) {
	// 	window.drawRect(collider->getGlobalBounds(), Color::Blue);
	// }

	// window.drawPoint(getOwner()->getPosition(), Color::Green);
}

bool Sprite::hasTexture() const {
	return m_textureID > 0;
}



IDtype Sprite::loadTextureFromFile(const std::string& fileName) {
	TextureManager& textures = getOwner()->CONTEXT->warehouse->getManager<TextureManager>();
	std::optional<fs::path> p = textures.findFile(fileName);
	if (!p.has_value()) {
		return 0;
	}

	m_textureID = textures.create(p.value());

	SDL_Texture* textureObj = textures.at(m_textureID).get();

	// Initial textureRect is the whole dimension of the texture.
	m_textureRect.l = 0;
	m_textureRect.t = 0;
	SDL_QueryTexture(textureObj, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

	return m_textureID;
}

void Sprite::setTexture(IDtype textureID) {
	if (textureID == 0) {
		std::cout << "Sprite texture being set to 0. Ignored" << std::endl;
		return; 
	}
	SDL_Texture* textureObj = getOwner()->CONTEXT->warehouse->getManager<TextureManager>().at(textureID).get();
	if(textureObj == nullptr) {
		std::cout << "Sprite's new texture turned out to be nullptr. Ignored." << std::endl;
	}

	m_textureID = textureID;

	//
	m_textureRect.l = 0;
	m_textureRect.t = 0;
	SDL_QueryTexture(textureObj, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

void Sprite::setTexture(IDtype textureID, const IntRect& rect) {
	SDL_Texture* textureObj = getOwner()->CONTEXT->warehouse->getManager<TextureManager>().at(textureID).get();
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
