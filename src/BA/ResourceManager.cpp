#include "BA/ResourceManager.hpp"

namespace ba {

#ifdef __linux__
	const path ResourceManager::BASE_DIR{"/opt/bit-alchemy/assets"};
#else
	const path ResourceManager::BASE_DIR{std::filesystem::current_path() / path{"assets"}};
#endif

ResourceManager::ResourceManager(SDL_Renderer* rend) : 
	m_renderer(rend),
	m_paths({
		BASE_DIR / path{"Textures"},
		BASE_DIR / path{"Fonts"}
	})
{

}

unsigned int ResourceManager::loadTexture(const std::string& fileName) {
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
	unsigned int id = ++textureCount;
	texturesMap.insert_or_assign(id, newTexture);
	
	return id;
}

unsigned int ResourceManager::loadFont(const std::string& fileName, int fontSize) {
	path file(m_paths[FONTS_PATH] / path{fileName});
	TTF_Font* newFont = TTF_OpenFont(file.c_str(), fontSize);
	if (newFont == NULL) {
		throw std::invalid_argument(TTF_GetError());
	}

	unsigned int id = ++fontCount;
	fontsMap.insert_or_assign(id,  newFont);

	return id;
}

SDL_Texture* ResourceManager::getTexture(unsigned int id) const {
	auto search = texturesMap.find(id);
	if (search == texturesMap.end())
		return NULL;
	return search->second;
}

TTF_Font* ResourceManager::getFont(unsigned int id) const {
	auto search = fontsMap.find(id);
	if (search == fontsMap.end())
		return NULL;
	return search->second;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

} // namespace ba