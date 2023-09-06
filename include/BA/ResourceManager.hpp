#pragma once

#include <array>
#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#include <BA/Types.hpp>

namespace fs = std::filesystem;
// using std::filesystem::path;

namespace ba {

class ResourceManager {
public:
	/*********************************
	 * CONSTANTS FOR INDEXES
	**********************************/
	static const std::size_t TEXTURES = 0;
	static const std::size_t SOUNDS = 1;
	static const std::size_t MUSICS = 2;
	static const std::size_t FONTS = 3;

public: // Methods and Constructors
	ResourceManager() = delete;
	ResourceManager(SDL_Renderer* rend);

	/***********************************************************************
	 * @brief Opens a text/xml file and stores the text in memory.
	 *
	 * @param fileName The file name of the file to be read.
	 * @param index Specifies which sub-directory to look for. Defaulted to
	 * Textures sub-directory as .tsx and .tmx files are assumed to be stored
	 * within it.
	 *
	 * @return the ID of the stored text data.
	************************************************************************/
	IDtype loadXML(const std::string& fileName, std::size_t index = TEXTURES);

	/*****************************************
	 * loadTexture()
	 * @brief Creates an SDL_Texture* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded SDL_Texture for future access.
	*****************************************/
	IDtype loadTexture(const std::string& fileName);

	/****************************************
	 * addTexture()
	 * @brief Adds the given texture and store it into memory.
	 * @param texture The texture to be stored.
	 * @returns the ID of the stored SDL_Texture for future access.
	*****************************************/
	IDtype addTexture(SDL_Texture* texture);

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

	/***********************************************************************
	 * @brief Get the String object
	 *
	 * @param id the ID that refers to the string
	 * @return the string
	************************************************************************/
	const std::string& getString(IDtype id) const noexcept;

	/*****************************************
	 * getTexture()
	 * @returns a pointer to an SDL_Texture referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	SDL_Texture* getTexture(IDtype id) const noexcept;

	/****************************************
	 * getSound()
	 * @returns a pointer to a Mix_Chunk referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	Mix_Chunk* getSound(IDtype id) const noexcept;

	/****************************************
	 * getMusic()
	 * @returns a pointer to a Mix_Music referred to by the given id. Returns NULL for invalid id.
	*****************************************/
	Mix_Music* getMusic(IDtype id) const noexcept;

	/*****************************************
	 * getFont()
	 * @returns a pointer to an TTF_Font referred to by the given id. Returns NULL  for invalid id.
	*****************************************/
	TTF_Font* getFont(IDtype id) const noexcept;

	/***********************************************************************
	 * @brief Sets the renderer used by this ResourceManager for creating and
	 * manipulating Textures.
	 *
	 * @param renderer The renderer to use.
	************************************************************************/
	void setRenderer(SDL_Renderer* renderer);


public:
	static void addToSearchPaths(const std::string& dir);
	static void addToSearchPaths(const fs::path& dir);

	static const std::vector<fs::path>& getBaseDirs();

private:
	std::optional<fs::path> getExistingPath(const fs::path& suffixPath);

private:
	std::unordered_map<IDtype, std::string> stringMap;
	std::unordered_map<IDtype, SDL_Texture*> texturesMap;
	std::unordered_map<IDtype, Mix_Chunk*> soundsMap;
	std::unordered_map<IDtype, Mix_Music*> musicsMap;
	std::unordered_map<IDtype, TTF_Font*> fontsMap;

	IDtype stringCount = 0;
	IDtype textureCount = 0;
	IDtype soundCount = 0;
	IDtype musicCount = 0;
	IDtype fontCount = 0;

	SDL_Renderer* m_renderer;


	/*********************************
	 * ARRAY CONSTANT
	**********************************/
	static const std::array<fs::path, 4>	sk_PATHS;

	/*********************************
	 * BASE-DIRECTORY
	*********************************/
	static std::vector<fs::path> sk_DIRS; // arrays of possible directories to find assets.

}; // class ResourceManager

} // namespace ba
