#include "BA/ResourceManager.hpp"

namespace ba {

#ifdef __linux__
	const path ResourceManager::BASE_DIR{"/usr/local/share/bit-alchemy/assets"};
#else
	const path ResourceManager::BASE_DIR{std::filesystem::current_path() / path{"assets"}};
#endif

ResourceManager::ResourceManager(SDL_Renderer* rend) : 
	m_renderer(rend),
	m_paths({
		BASE_DIR / path{"Textures"},
		BASE_DIR / path{"Sounds"},
		BASE_DIR / path{"Musics"},
		BASE_DIR / path{"Fonts"}
	})
{

}

IDtype ResourceManager::loadTexture(const std::string& fileName) {
	path file(m_paths[TEXTURES_PATH] / path{fileName});
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());
	if (loadedSurface == NULL) {
		throw std::invalid_argument(IMG_GetError());
	}

	newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
	if (newTexture == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
	IDtype id = ++textureCount;
	texturesMap.insert_or_assign(id, newTexture);
	
	return id;
}

IDtype ResourceManager::loadSound(const std::string& fileName) {
	path file(m_paths[SOUNDS_PATH] / path{fileName});
	Mix_Chunk* newSound = Mix_LoadWAV(file.c_str());
	if(newSound == NULL) {
		throw std::invalid_argument(Mix_GetError());
	}
	IDtype id = ++soundCount;
	soundsMap.insert_or_assign(id, newSound);

	return id;
}

IDtype ResourceManager::loadMusic(const std::string& fileName) {
	path file(m_paths[MUSICS_PATH] / path{fileName});
	Mix_Music* newMusic = Mix_LoadMUS(file.c_str());
	if(newMusic == NULL) {
		throw std::invalid_argument(Mix_GetError());
	}

	IDtype id = ++musicCount;
	musicsMap.insert_or_assign(id, newMusic);

	return id;
}

IDtype ResourceManager::loadFont(const std::string& fileName, int fontSize) {
	path file(m_paths[FONTS_PATH] / path{fileName});
	TTF_Font* newFont = TTF_OpenFont(file.c_str(), fontSize);
	if (newFont == NULL) {
		throw std::invalid_argument(TTF_GetError());
	}

	IDtype id = ++fontCount;
	fontsMap.insert_or_assign(id,  newFont);

	return id;
}

SDL_Texture* ResourceManager::getTexture(IDtype id) const {
	if(texturesMap.contains(id))
		return texturesMap.at(id);
	return NULL;
}

Mix_Chunk* ResourceManager::getSound(IDtype id) const {
	if(soundsMap.contains(id))
		return soundsMap.at(id);
	return NULL;
}

Mix_Music* ResourceManager::getMusic(IDtype id) const {
	if(musicsMap.contains(id))
		return musicsMap.at(id);
	return NULL;
}

TTF_Font* ResourceManager::getFont(IDtype id) const {
	if(fontsMap.contains(id))
		return fontsMap.at(id);
	return NULL;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

} // namespace ba