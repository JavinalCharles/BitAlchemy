#include <BA/Components/Text.hpp>
#include <BA/Entities/Entity.hpp>

#include <iostream>

using ba::Resources::FontManager;

namespace ba {

Text::Text(Entity* owner, IDtype layer) :
	Drawable(owner, layer)
{
}

Text::~Text() {
	SDL_DestroyTexture(m_textTexture);
	m_textTexture = nullptr;
}

IDtype Text::loadFontFromFile(const std::string& fileName, int fontSize) {
	m_fontID = m_owner->CONTEXT->warehouse->getManager<FontManager>().create(fileName, fontSize);
	m_updatedText = false;
	return m_fontID;
}

void Text::appendText(char ch, std::size_t count) {
	m_text.append(count, ch);
	m_updatedText = false;
}

void Text::appendText(const std::string& str) {
	m_text.append(str);
	m_updatedText = false;
}

void Text::appendText(const std::string& str, std::size_t pos, std::size_t count) {
	m_text.append(str, pos, count);
	m_updatedText = false;
}

void Text::setText(const std::string& newText) {
	if (m_text == newText)
		return;
	m_text = newText;
	m_updatedText = false;
}

const std::string& Text::getText() const {
	return m_text;
}

void Text::setColor(const Color& color) {
	m_textColor = color;
	m_updatedText = false;
}

void Text::setWrapLength(ba::uint32 wrapLength) {
	m_wrapLength = wrapLength;
	m_updatedText = false;
}

const Color& Text::getColor() const {
	return m_textColor;
}

void Text::setFontID(IDtype newFontID) {
	m_fontID = newFontID;
	m_updatedText = false;
}

IDtype Text::getFontID() const {
	return m_fontID;
}

uint32 Text::getWrapLength() const {
	return m_wrapLength;
}

const SDL_Texture* Text::getTexture() const {
	if (!m_updatedText) {
		updateText();
	}
	return m_textTexture;
}

void Text::draw(Window& window) {
	if (!m_updatedText) {
		updateText();
	}
	window.draw(m_textTexture, getGlobalBounds());
}

FloatRect Text::getLocalBounds() const {
	if (!m_updatedText) {
		updateText();
	}
	return m_rect;
}

FloatRect Text::getGlobalBounds() const {
	return getOwner()->getTransform().transformRect(getLocalBounds());
}

void Text::updateText() const {
	if (m_updatedText) {
		return;
	}

	if (m_textTexture != nullptr) {
		SDL_DestroyTexture(m_textTexture);
		m_textTexture = nullptr;
	}

	TTF_Font* font = m_owner->CONTEXT->warehouse->getManager<FontManager>().at(m_fontID).get();
	SDL_Color color = m_textColor.toSDL_Color();
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, m_text.c_str(), color, m_wrapLength);

	if (surface == nullptr) {
		throw std::runtime_error(TTF_GetError());
	}

	m_textTexture = SDL_CreateTextureFromSurface(m_owner->CONTEXT->window->getRenderer(), surface);
	m_rect.w = static_cast<int>(surface->w);
	m_rect.h = static_cast<int>(surface->h);

	SDL_FreeSurface(surface);
	surface = nullptr;

	m_updatedText = true;
}


} // namespace ba
