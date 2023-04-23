#include <BA/Components/Text.hpp>
#include <BA/Entities/Entity.hpp>

#include <iostream>

namespace ba {

Text::Text(Entity* owner, IDtype layer, IDtype order) :
	Drawable(owner, layer, order)
{
}

IDtype Text::loadFontFromFile(const std::string& fileName, int fontSize) {
	m_fontID = m_owner->CONTEXT->resources->loadFont(fileName, fontSize);
	updateText();
	return m_fontID;
}

void Text::setText(const std::string& newText) {
	if (m_text == newText)
		return;
	m_text = newText;
	m_updatedText = false;
	updateText();
}

const std::string& Text::getText() const {
	return m_text;
}

void Text::setColor(const Color& color) {
	m_textColor = color;
	m_updatedText = false;
	updateText();
}

const Color& Text::getColor() const {
	return m_textColor;
}

void Text::setFontID(IDtype newFontID) {
	m_fontID = newFontID;
	m_updatedText = false;
	updateText();
}

IDtype Text::getFontID() const {
	return m_fontID;
}

void Text::draw(Window& window) {
	// std::clog << "Drawing Text from entity #:" << m_owner->ID << std::endl;
	window.draw(m_textTexture, getGlobalBounds());
}

FloatRect Text::getLocalBounds() const {
	return m_rect;
}

FloatRect Text::getGlobalBounds() const {
	return getOwner()->getTransform().transformRect(getLocalBounds());
}

void Text::updateText() {
	if (m_updatedText)
		return;
	if (m_textTexture != nullptr) {
		SDL_DestroyTexture(m_textTexture);
		m_textTexture = nullptr;
	}
	
	TTF_Font* font = m_owner->CONTEXT->resources->getFont(m_fontID);
	SDL_Color color = m_textColor.toSDL_Color();
	SDL_Surface* surface = TTF_RenderText_Solid(font, m_text.c_str(), color);
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