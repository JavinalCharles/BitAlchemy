#include "BA/ResourceManager.hpp"

namespace ba {

const std::array<fs::path, 6> ResourceManager::sk_PATHS({
	fs::path("."),
	fs::path{"Textures"},
	fs::path{"Sounds"},
	fs::path{"Musics"},
	fs::path{"Fonts"},
	fs::path{"Strings"},
});

#ifdef __linux__
	std::vector<fs::path> ResourceManager::sk_DIRS {
		fs::path("/usr/local/share/bit-alchemy/assets"),
	};
#else
	// TODO
#endif

ResourceManager::ResourceManager() = default;

ResourceManager::ResourceManager(SDL_Renderer* rend) :
	m_renderer(rend)
{

}

IDtype ResourceManager::loadXML(const std::string& fileName, std::size_t index) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[index] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}
	fs::path p = opt.value();

	std::ifstream f(p.string());
	if (f.fail()) {
		throw std::invalid_argument("Cannot open file: " + p.string());
	}
	std::stringstream stream;
	stream << f.rdbuf();
	f.close();

	IDtype id = ++stringCount;
	stringMap.insert_or_assign(id, stream.str());

	return id;
}

IDtype ResourceManager::loadTexture(const std::string& fileName) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[TEXTURES] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}

	fs::path file = opt.value();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == nullptr) {
		throw std::invalid_argument(IMG_GetError());
	}

	newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
	if (newTexture == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	SDL_FreeSurface(loadedSurface);
	IDtype id = ++textureCount;

	texturesMap.insert_or_assign(id, newTexture);

	return id;
}



IDtype ResourceManager::addTexture(SDL_Texture* texture) {
	IDtype id = ++textureCount;
	texturesMap.insert_or_assign(id, texture);

	return id;
}

IDtype ResourceManager::loadSound(const std::string& fileName) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[SOUNDS] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}

	fs::path file = opt.value();

	Mix_Chunk* newSound = Mix_LoadWAV(file.c_str());
	if(newSound == NULL) {
		throw std::invalid_argument(Mix_GetError());
	}
	IDtype id = ++soundCount;
	soundsMap.insert_or_assign(id, newSound);

	return id;
}

IDtype ResourceManager::loadMusic(const std::string& fileName) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[MUSICS] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}

	fs::path file = opt.value();
	Mix_Music* newMusic = Mix_LoadMUS(file.c_str());
	if(newMusic == NULL) {
		throw std::invalid_argument(Mix_GetError());
	}

	IDtype id = ++musicCount;
	musicsMap.insert_or_assign(id, newMusic);

	return id;
}

IDtype ResourceManager::loadFont(const std::string& fileName, int fontSize) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[FONTS] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}

	fs::path file = opt.value();
	TTF_Font* newFont = TTF_OpenFont(file.c_str(), fontSize);
	if (newFont == NULL) {
		throw std::invalid_argument(TTF_GetError());
	}

	IDtype id = ++fontCount;
	fontsMap.insert_or_assign(id,  newFont);

	return id;
}

const std::string& ResourceManager::getString(IDtype id) const noexcept {
	if (stringMap.contains(id))
		return stringMap.at(id);

	return stringMap.at(0u);
}

SDL_Texture* ResourceManager::getTexture(IDtype id) const noexcept {
	if(texturesMap.contains(id))
		return texturesMap.at(id);

	return NULL;
}

Mix_Chunk* ResourceManager::getSound(IDtype id) const noexcept {
	if(soundsMap.contains(id))
		return soundsMap.at(id);
	return NULL;
}

Mix_Music* ResourceManager::getMusic(IDtype id) const noexcept {
	if(musicsMap.contains(id))
		return musicsMap.at(id);
	return NULL;
}

TTF_Font* ResourceManager::getFont(IDtype id) const noexcept {
	if(fontsMap.contains(id))
		return fontsMap.at(id);
	return NULL;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}


void ResourceManager::addToSearchPaths(const std::string& dir) {
	ResourceManager::addToSearchPaths(fs::path(dir));
}

void ResourceManager::addToSearchPaths(const fs::path& dir) {
	if (dir.has_filename() || !dir.is_absolute() || !fs::exists(dir)) {
		throw std::invalid_argument("ResourceManager::addToSearchPaths() provided argument: \"" + dir.string() + "\" is not a valid path");
	}

	sk_DIRS.push_back(dir);
}

const std::vector<fs::path>& ResourceManager::getBaseDirs() {
	return sk_DIRS;
}

std::optional<fs::path> ResourceManager::getExistingPath(const fs::path& suffixPath) {
	for (const fs::path& basePath : sk_DIRS) {
		fs::path p(basePath / suffixPath);
		if (fs::exists(p)) {
			return std::make_optional<fs::path>(p);
		}
	}
	return std::nullopt;
}

} // namespace ba
