#pragma once

#include <stdexcept>
#include <string>

#include <BA/Components/Drawable.hpp>
#include <BA/Types.hpp>
#include <BA/Utilities/Color.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

class Text : public Drawable {
public:
	explicit Text(Entity* owner, IDtype drawLayer = 0, IDtype sortOrder = 0);

	virtual void draw(Window& window) override;

	IDtype loadFontFromFile(const std::string& fileName, int fontSize);

	void setText(const std::string& newText);
	const std::string& getText() const;

	void setColor(const Color& color);
	const Color& getColor() const;

	void setFontID(IDtype newFontID);
	IDtype getFontID() const;

	virtual FloatRect getLocalBounds() const override;
	virtual FloatRect getGlobalBounds() const override;

private:
	void updateFont();
	void updateText();


	std::string 	m_text{"Text"};

	IDtype			m_fontID{};
	Color 			m_textColor = Color::White;

	SDL_Texture*	m_textTexture = nullptr;
	IntRect			m_rect{0, 0, 0, 0};
	bool			m_updatedText = true;

}; // class Text

} // namespace ba
