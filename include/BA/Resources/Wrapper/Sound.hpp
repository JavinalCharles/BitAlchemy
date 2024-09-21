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
	 *  - The last remaining Soundt owning the pointer is destroyed.
	 *  - The last remaining Soundt owning the pointer is reassigned via means of operator= or reset().
	 * 
	 */
	class Sound {
	public:
		Sound();
		explicit Sound(const std::string& file);
		Sound(const Sound& other);
		Sound(Sound&& other);
		~Sound();

		Sound& operator=(const Sound& rhs);
		Sound& operator=(Sound&& rhs);

		Mix_Chunk* loadSound(const std::string& file);

		constexpr Mix_Chunk* get() const;

		void reset();
	private:
		void initRefCounter();
	private:
		Mix_Chunk* m_sound = nullptr;
		int* m_refCount = nullptr;
	}; // class Sound

	constexpr Mix_Chunk* Sound::get() const {
		return m_sound;
	}
} // namespace Resource
} // namespace ba