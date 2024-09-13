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
	explicit Text(Entity* owner, IDtype drawLayer = DEFAULT_RENDER_LAYER);

	virtual ~Text();

	virtual void draw(Window& window) override;

	/**
	 * MODIFIERS
	**/

	/**
	 * @brief Appends count copies of character ch at the end of the underlying
	 * text object.
	 *
	 * @param ch the character to be appended.
	**/
	void appendText(char ch, std::size_t count = 1u);

	/**
	 * @brief Appends str to the end of the underlying text object.
	 *
	 * @param str the string to be appended.
	**/
	void appendText(const std::string& str);

	/**
	 * @brief Appends substring[pos, pos + count] of str to the end of the
	 * underlying text object.
	 *
	 * @param str the text to be appended.
	**/
	void appendText(const std::string& str, std::size_t pos, std::size_t count = std::string::npos);

	/**
	 * @brief Uses the owning entities resources CONTEXT to load a font from
	 * file.
	 *
	 * @param fileName the name of the file.
	 * @param fontSize the preferred size to load the font with.
	 * @return the ID key of the loaded font.
	 *
	 * Uses the owning entities resources CONTEXT to load a font from. Might
	 * throw an std::invalid_argument exception if fileName does not exists
	 * within the ResourceManager's search directories.
	**/
	IDtype loadFontFromFile(const std::string& fileName, int fontSize);

	/**
	 * @brief Set the Text object.
	 *
	 * @param newText the string to set the underlying text object to.
	 *
	 * This method replaces the currently stored stored text object with the
	 * new newText.
	**/
	void setText(const std::string& newText);

	/**
	 * @brief Set the Color of the text.
	 *
	 * @param color the color of the text.
	**/
	void setColor(const Color& color);

	/**
	 * @brief Set the font of the text to one referred to by newFontID.
	 *
	 * @param newFontID the ID/key to the new font.
	**/
	void setFontID(IDtype newFontID);

	/**
	 * @brief Set the Wrap Length of the text.
	 *
	 * @param wrapLength the length by which the text will attempt to wrap on.
	 *
	 * Text is wrapped to multiple lines on line endings and on word boundaries
	 * if it extends wrapLength in pixels. If wrapLength is set to 0, the text
	 * will wrap only on new line characters.
	 * Note: wrapLength is set to 0 by default.
	**/
	void setWrapLength(uint32 wrapLength);

	/**
	 * @brief Get the Text object
	 *
	 * @return A reference to the underlying text object.
	**/
	const std::string& getText() const;

	/**
	 * @brief Get the Color object
	 *
	 * @return A reference to the RGB-A Color of the text.
	**/
	const Color& getColor() const;

	/**
	 * @brief Get the font ID of the text.
	 *
	 * @return the ID/key to the current font of the object.
	**/
	IDtype getFontID() const;

	/**
	 * @brief Get the text's Wrap Length in pixels
	 *
	 * @return the text's wrap length.
	**/
	uint32 getWrapLength() const;

	/**
	 * @brief Get the Texture of the text.
	 *
	 * @return A pointer to the texture of the Text.
	**/
	const SDL_Texture* getTexture() const;

	virtual FloatRect getLocalBounds() const override;
	virtual FloatRect getGlobalBounds() const override;
private:
	void updateText() const;

private:
	std::string 	m_text{""};
	uint32 			m_wrapLength = 0u;

	IDtype			m_fontID = 0u;
	Color 			m_textColor = Color::White;

	mutable SDL_Texture*	m_textTexture = nullptr;
	mutable IntRect			m_rect{0, 0, 0, 0};
	mutable bool			m_updatedText = true;
}; // class Text

} // namespace ba
