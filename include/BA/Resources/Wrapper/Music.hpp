#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL_mixer.h>

namespace ba{
namespace Resources {
		/**
	 * @brief A wrappef for Mix_Music
	 * 
	 * This class acts as a wrapper for Mix_Music and provides 
	 * an OOP means of managing the stored object, and also acts
	 * as its own smart pointer that keep tracks of how many objects
	 * share ownership to the same pointer and 
	 * automatically calls Mix_FreeMusic() once one of the 
	 * following happens:
	 *  - The last remaining Music owning the pointer is destroyed.
	 *  - The last remaining Music owning the pointer is reassigned via means of operator= or reset().
	 * 
	 */
	class Music {
	public:
		///@{
		/**
		 * @name Constructors
		 * @brief Construct the object
		 * 
		 * Initalizes the object and if a file is given, calls the
		 * loadMusic() method.
		 * @param file The music file's path and filename.
		 * @param other The other object to be copied/move.
		 * 
		 */
		Music();
		Music(const std::string& file);
		Music(const Music& other);
		Music(Music&& other);
		///@}

		/// @brief Destroys the object by calling the reset() method
		~Music();

		///@{
		/**
		 * @brief Resets this object and replaced it values from rhs.
		 * 
		 * @param rhs the object to be copied/moved to this.
		 * @return this 
		 */
		Music& operator=(const Music& rhs);
		Music& operator=(Music&& rhs);
		///@}

		/**
		 * @brief Creates the music object from file
		 * 
		 * @param file the music's path and filename.
		 * @return the created music object or nullptr if an error occured.
		 * 
		 * @note If this object already loaded a music (via prior calls
		 * of loadMusic(), then reset() shall be called first.
		 */
		Mix_Music* loadMusic(const std::string& file);

		/**
		 * @brief returns the internally managed object.
		 * 
		 * @return the managed object or nullptr if none.
		 */
		constexpr Mix_Music* get() const noexcept;

		/**
		 * @brief release ownership of the managed object.
		 * 
		 * This decrements the reference counter and if said counter
		 * reaches a value < 1, frees up the allocated memory for 
		 * the managed object.
		 * 
		 */
		void reset();
	private:
		void initRefCounter();
	private:
		Mix_Music* m_music = nullptr;
		int* m_refCount = nullptr;
	}; // class Music


	constexpr Mix_Music* Music::get() const noexcept {
		return m_music;
	}
} // namespace Resources
} // namespace ba