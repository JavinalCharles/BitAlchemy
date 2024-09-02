#pragma once

#include <any>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <tinyxml2/tinyxml2.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <BA/Exceptions/Inaccessible.hpp>
#include "BA/Types.hpp"
// #include "BA/Tools/ConfigMap.hpp"
#include "BA/Tools/DebugHelper.hpp"

namespace fs = std::filesystem;
// using std::filesystem::path;

namespace ba {

class ResourceManager {
public:
	/**
	 * CONSTANTS FOR INDEXES
	**/
	enum ResourceType: IDtype {
		NO_RESTYPE = 0,
		CONFIGS,
		TEXTURES,
		SOUNDS,
		MUSICS,
		FONTS,
		STRINGS,
		XMLDOC,
	};

public: // Methods and Constructors
	ResourceManager();
	ResourceManager(SDL_Renderer* rend);

	ResourceManager(ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager& other) = delete;

	~ResourceManager();

	////////////////////////////////////////////////////////////////////////
	// RESOURCES LOADING
	////////////////////////////////////////////////////////////////////////
	/**
	 * @brief Loads the applications configuration file.
	 * 
	 * @param fileName the name of the configFile.
	 * 
	 * @return true if the configurations has been successfully loaded. false
	 * otherwise.
	 */
	void loadConfig(const std::string& fileName);

	/**
	 * @brief sets a specific config to a certain value.
	 * 
	 * @return true if object is successfully inserted.
	 **/
	bool setConfig(ConfigID id, std::any value);

	/**
	 * loadTexture()
	 * @brief Creates an SDL_Texture* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded SDL_Texture for future access.
	**/
	IDtype loadTexture(const std::string& fileName);

	/**
	 * addTexture()
	 * @brief Adds the given texture and store it into memory.
	 * @param texture The texture to be stored.
	 * @returns the ID of the stored SDL_Texture for future access.
	**/
	IDtype addTexture(SDL_Texture* texture);

	/**
	 * loadMusic()
	 * @brief Creats a Mix_Chunk* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded Mix_Chunk for future access.
	**/
	IDtype loadSound(const std::string& fileName);

	/**
	 * loadMusic()
	 * @brief Creates an Mix_Music* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded Mix_Music for future access.
	**/
	IDtype loadMusic(const std::string& fileName);

	/**
	 * loadFont()
	 * @brief Creates a TTF_Font* object from fileName and stores it into memory.
	 * @param fileName The file's name in a path relative to BASE_DIR and respective subdirectory.
	 * @returns the ID of the loaded TTF_Font for future access.
	**/
	IDtype loadFont(const std::string& fileName, int fontSize);

	/**
	 * @brief Opens a text/xml file and stores the text in memory.
	 *
	 * @param fileName The file name of the file to be read.
	 *
	 * @return the ID of the stored text data.
	**/
	IDtype loadXML(const std::string& fileName);


	////////////////////////////////////////////////////////////////////////
	// RESOURCES EXTRACTION
	////////////////////////////////////////////////////////////////////////


	/**
	 * @brief Get the config data
	 * 
	 * @param id the ID of the config.
	 * @return an std::any object that can be casted into either std::string or
	 * int, depending on the config. If id is non-existent in the map, then
	 * the method returns an empty std::any. Use std::any::has_value() to check.
	 **/
	std::any getConfig(ConfigID id) const noexcept;

	/**
	 * @brief Get the String object
	 *
	 * @param id the ID that refers to the string
	 * @return the string, if the id exist. An empty string otherwise.
	**/
	const std::string& getString(IDtype id) const noexcept;

	/**
	 * getTexture()
	 * @returns a pointer to an SDL_Texture referred to by the given id. Returns NULL for invalid id.
	**/
	SDL_Texture* getTexture(IDtype id) const noexcept;

	/**
	 * getSound()
	 * @returns a pointer to a Mix_Chunk referred to by the given id. Returns NULL for invalid id.
	**/
	Mix_Chunk* getSound(IDtype id) const noexcept;

	/**
	 * getMusic()
	 * @returns a pointer to a Mix_Music referred to by the given id. Returns NULL for invalid id.
	**/
	Mix_Music* getMusic(IDtype id) const noexcept;

	/**
	 * getFont()
	 * @returns a pointer to an TTF_Font referred to by the given id. Returns NULL  for invalid id.
	**/
	TTF_Font* getFont(IDtype id) const noexcept;

	/**
	 * getXML()
	 * @returns a const reference to the XMLDocument referred to by id.
	 */
	const tinyxml2::XMLDocument* getXML(IDtype id) const noexcept;

	////////////////////////////////////////////////////////////////////////
	// MODIFIERS
	////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Sets the renderer used by this ResourceManager for creating and
	 * manipulating Textures.
	 *
	 * @param renderer The renderer to use.
	**/
	void setRenderer(SDL_Renderer* renderer);

public:
	////////////////////////////////////////////////////////////////////////
	// STATIC MODIFIERS
	////////////////////////////////////////////////////////////////////////
	static void addToSearchPaths(const std::string& dir);
	static void addToSearchPaths(const fs::path& dir);

	static const std::vector<fs::path>& getBaseDirs();

private:
	std::optional<fs::path> getExistingPath(const fs::path& suffixPath);

	void saveCurrentConfiguration();

private:
	// TODO: Considering the tediousness of having to maintain quite a numerous number resource maps
	// And that the number of different resources just keeps growing, prompting me to make more load, get, and free methods for each type of resources 
	// and that there is no certainty for a game needing to maintain this much variety in resources,
	// It is probably better to create a separate class to abstract all of the common functionalities
	// of loading, storing, getting, updating, and freeing all these resources
	// and have ResourceManager provide a means to include only the resource it needs.
	// i.e
	// ```
	// ResourceManager res;
	// res->includeResourceHandler<TextureHandler>();
	// auto& textures = res->getResourceHandler<TextureHandler>();
	// ... //  do something.
	// ```
	std::unordered_map<IDtype, std::any> configMap;
	std::unordered_map<IDtype, std::string> stringMap = {{0u, ""}};
	std::unordered_map<IDtype, SDL_Texture*> texturesMap;
	std::unordered_map<IDtype, Mix_Chunk*> soundsMap;
	std::unordered_map<IDtype, Mix_Music*> musicsMap;
	std::unordered_map<IDtype, TTF_Font*> fontsMap;
	std::unordered_map<IDtype, std::unique_ptr<tinyxml2::XMLDocument>> xmlMap;

	IDtype stringCount = 0;
	IDtype textureCount = 0;
	IDtype soundCount = 0;
	IDtype musicCount = 0;
	IDtype fontCount = 0;
	IDtype xmlDocCount = 0;

	SDL_Renderer* m_renderer = nullptr;
	std::string m_configFile = "";
private:
	/**
	 * STATIC CONSTANT ARRAY
	**/
	static const std::array<fs::path, 8>	sk_PATHS;

	/**
	 * BASE-DIRECTORIES
	**/
	static std::vector<fs::path> s_DIRS;// arrays of possible directories to find assets.

	/**
	 * 
	 **/
	static const std::map<std::string, ConfigID> sk_configStringMap;
	
	static const std::unordered_map<ConfigID, std::pair<std::string, const std::type_info&>> sk_configIDMap;
}; // class ResourceManager

} // namespace ba
