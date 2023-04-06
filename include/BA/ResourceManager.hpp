#pragma once

#include <array>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <BA/Types.hpp>

using std::filesystem::path;

namespace ba {

class ResourceManager {
public: // Methods and Constructors
	ResourceManager() = delete;
	ResourceManager(SDL_Renderer* rend);

	/*****************************************
	 * loadTexture()
	 * @brief Creates an SDL_Texture* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory. 
	 * @returns the ID of the loaded SDL_Texture for future access.
	*****************************************/
	IDtype loadTexture(const std::string& fileName);

	/****************************************
	 * loadMusic()
	 * @brief Creats a Mix_Chunk* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded Mix_Chunk for future access.
	*****************************************/
	IDtype loadSound(const std::string& fileName);

	/****************************************
	 * loadMusic()
	 * @brief Creates an Mix_Music* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded Mix_Music for future access.
	*****************************************/
	IDtype loadMusic(const std::string& fileName);

	/****************************************
	 * loadFont()
	 * @brief Creates a TTF_Font* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded TTF_Font for future access.
	****************************************/
	IDtype loadFont(const std::string& fileName, int fontSize);

	/*****************************************
	 * getTexture()
	 * @returns a pointer to an SDL_Texture referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	SDL_Texture* getTexture(IDtype id) const;

	/****************************************
	 * getSound()
	 * @returns a pointer to a Mix_Chunk referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	Mix_Chunk* getSound(IDtype id) const;

	/****************************************
	 * getMusic()
	 * @returns a pointer to a Mix_Music referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	Mix_Music* getMusic(IDtype id) const;

	/*****************************************
	 * getFont()
	 * @returns a pointer to an TTF_Font referred to by the given id. Returns NULL  for invalid id.
	*****************************************/
	TTF_Font* getFont(IDtype id) const;


	void setRenderer(SDL_Renderer* renderer);
private:
	std::unordered_map<IDtype, SDL_Texture*> texturesMap;
	std::unordered_map<IDtype, Mix_Chunk*> soundsMap;
	std::unordered_map<IDtype, Mix_Music*> musicsMap;
	std::unordered_map<IDtype, TTF_Font*> fontsMap;
	

	IDtype textureCount = 0;
	IDtype soundCount = 0;
	IDtype musicCount = 0;
	IDtype fontCount = 0;

	SDL_Renderer* m_renderer; 

	std::array<std::filesystem::path, 4>	m_paths;
	/*********************************
	 * CONSTANTS FOR INDEXES
	**********************************/
	static const std::size_t TEXTURES_PATH = 0;
	static const std::size_t SOUNDS_PATH = 1;
	static const std::size_t MUSICS_PATH = 2;
	static const std::size_t FONTS_PATH = 3;
	/*********************************
	 * BASE-DIRECTORY
	*********************************/
	static const path BASE_DIR;

}; // class ResourceManager

} // namespace ba