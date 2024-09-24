#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL_mixer.h>

namespace ba{
namespace Resources {

	/**
	 * @brief A wrappef for Mix_Chunk
	 * 
	 * This class acts as a wrapper for Mix_Chunk and provides 
	 * an OOP means of managing the stored object, and also acts
	 * as its own smart pointer that keep tracks of how many objects
	 * share ownership to the same pointer and 
	 * automatically calls Mix_FreeChunk() once one of the 
	 * following happens:
	 *  - The last remaining Sound owning the pointer is destroyed.
	 *  - The last remaining Sound owning the pointer is reassigned via means of operator= or reset().
	 * 
	 */
	class Sound {
	public:
		///@{
		/**
		 * @brief Construct a sound object
		 * 
		 * Initializes the object and calls  the relevant loadSound()
		 * method if a file is given.
		 * 
		 * @param file the sound's file path.
		 * @param other the other Sound object to be copied/moved.
		 */
		Sound();
		Sound(const std::string& file);
		Sound(const Sound& other);
		Sound(Sound&& other);
		///@}

		/// @brief destroys the object by calling reset().
		~Sound();

		///@{
		/**
		 * @brief Copies/Moves rhs to this object.
		 * @param rhs the other object to be copied/moved.
		 * @returns this
		 */
		Sound& operator=(const Sound& rhs);
		Sound& operator=(Sound&& rhs);
		///@}

		///@{
		/**
		 * @brief loads sound from a file.
		 * @param file the sound's filepath.
		 * @returns the loaded chunk or nullptr if an error occured.
		 */
		Mix_Chunk* loadSound(const std::string& file);
		///@}

		/** 
		 * @brief returns a pointer to the internally managed object.
		 * @return the pointer.
		 */
		constexpr Mix_Chunk* get() const noexcept;

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
		Mix_Chunk* m_sound = nullptr;
		int* m_refCount = nullptr;
	}; // class Sound

	constexpr Mix_Chunk* Sound::get() const noexcept {
		return m_sound;
	}
} // namespace Resource
} // namespace ba