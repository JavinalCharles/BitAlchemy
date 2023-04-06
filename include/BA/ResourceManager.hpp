#pragma once

#include <array>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using std::filesystem::path;

namespace ba {

class ResourceManager {
public: // Methods and Constructors
	ResourceManager() = delete;
	ResourceManager(SDL_Renderer* rend);

	/**
	 * loadTexture()
	 * - Creates an SDL_Texture* object from path and stores it into memory. 
	 * Returns the id of the loaded SDL_Texture for future access.
	*/
	unsigned int loadTexture(const std::string& fileName);
	/**
	 * loadFont()
	 * - Creates a TTF_Font* object from path and stores it into memory.
	 * Returns the id of the loaded TTF_Font for future access.
	*/
	unsigned int loadFont(const std::string& fileName, int fontSize);

	/**
	 * getTexture()
	 * - Returns a pointer to SDL_Texture referred to by given id. Returns NULL for invalid id.
	*/
	SDL_Texture* getTexture(unsigned int id) const;

	/**
	 * getFont()
	 * - Returns a pointer to TTF_Font referred to by given id. Returns NULL  for invalid id.
	*/
	TTF_Font* getFont(unsigned int id) const;

	void setRenderer(SDL_Renderer* renderer);

private:
	std::unordered_map<unsigned int, SDL_Texture*> texturesMap;
	unsigned int textureCount = 0;
	std::unordered_map<unsigned int, TTF_Font*> fontsMap;
	unsigned int fontCount = 0;
	// TODO: Map for audios/musics

	SDL_Renderer* m_renderer; 

	std::array<std::filesystem::path, 2>	m_paths;
	/*********************************
	 * CONSTANTS FOR INDEXES
	**********************************/
	static const std::size_t TEXTURES_PATH = 0;
	static const std::size_t FONTS_PATH = 1;
	/*********************************
	 * BASE-DIRECTORY
	*********************************/
	static const path BASE_DIR;

}; // class ResourceManager

} // namespace ba