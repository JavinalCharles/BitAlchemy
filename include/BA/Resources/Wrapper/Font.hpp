#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL_ttf.h>

#include <BA/Utilities/Vector2.hpp>

namespace ba {
namespace Resources {
	/**
	 * @brief A wrappef for TTF_Font
	 * 
	 * This class acts as a wrapper for TTF_Font and provides 
	 * an OOP means of managing the stored object, and also acts
	 * as its own smart pointer that keep tracks of how many objects
	 * share ownership to the same pointer and 
	 * automatically calls TTF_CloseFont() once one of the 
	 * following happens:
	 *  - The last remaining Font owning the pointer is destroyed.
	 *  - The last remaining Font owning the pointer is reassigned via means of operator= or reset().
	 * 
	 */
	class Font {
	public:
		/// TODO: methods to modify the stored object.

		///@{
		/**
		 * Constructs the Font
		 * 
		 * Initializes this object and for constuctors with parameters,
		 * calls the relevant Font::openFont() method.
		 * 
		 * @param file the font file.
		 * @param ptsize point size to use.
		 * @param index specifies which "face" to use from the font file
		 * for files that have multiple faces in them.
		 * @param dpi scaling for scaleable fonts (eg. TrueType)
		 *  - dpi.x - horizontal dpi (hdpi)
		 *  - dpi.y - vertical dpi (vdpi)
		 * 
		 * @param other The object to be copied/moved to this object.
		 */
		Font();
		Font(const std::string& file, int ptsize);
		Font(const std::string& file, int ptsize, long index);
		Font(const std::string& file, int ptsize, const Vector2u& dpi);
		Font(const std::string& file, int ptsize, long index, const Vector2u& dpi);
		Font(const Font& other);
		Font(Font&& other);
		///@}

		/**
		 * @brief Destroy the Font object
		 * 
		 * calls reset()
		 */
		~Font();

		Font& operator=(const Font& rhs);
		Font& operator=(Font&& rhs);


		///@{
		/**
		 * @brief creates a font from a file.
		 * 
		 * @param file the font file.
		 * @param ptsize point size to use.
		 * @param index specifies which "face" to use from the font file
		 * for files that have multiple faces in them.
		 * @param dpi scaling for scaleable fonts (eg. TrueType)
		 *  - dpi.x - horizontal dpi (hdpi)
		 *  - dpi.y - vertical dpi (vdpi)
		 * @returns The created font, or nullptr if an error occured.
		 * 
		 */
		TTF_Font* openFont(const std::string& file, int ptsize);
		TTF_Font* openFont(const std::string& file, int ptsize, long index);
		TTF_Font* openFont(const std::string& file, int ptsiza, const Vector2u& dpi);
		TTF_Font* openFont(const std::string& file, int ptsize, long index, const Vector2u& dpi);
		///@}

		/**
		 * @brief returns a pointer to the internally managed object. 
		 */
		constexpr TTF_Font* get() const noexcept;

		/**
		 * @brief resets this object
		 * 
		 * This method decrements the stored reference counter and if
		 * said counter reaches any value less than 1, frees up the
		 * allocated memory for the object and the reference counter.
		 */
		void reset();
	private:
		void initializeRefCount();
	private:
		TTF_Font* m_font = nullptr;
		int* m_refCount = nullptr;
	}; // class Font

	constexpr TTF_Font* Font::get() const noexcept {
		return m_font;
	}
} // namespace Resource
} // namespace ba