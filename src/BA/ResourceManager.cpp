#include "BA/ResourceManager.hpp"

namespace ba {

const std::array<fs::path, 8> ResourceManager::sk_PATHS({
	fs::path("."),
	fs::path("Configs"),
	fs::path{"Textures"},
	fs::path{"Sounds"},
	fs::path{"Musics"},
	fs::path{"Fonts"},
	fs::path{"Strings"},
	fs::path("XML")
});

std::vector<fs::path> ResourceManager::s_DIRS;

const std::map<std::string, ConfigID> ResourceManager::sk_configStringMap({
	{"PROFILE_NAME", PROFILE_NAME},
	{"WINDOW_WIDTH", WINDOW_WIDTH},
	{"WINDOW_HEIGHT", WINDOW_HEIGHT},
	{"WINDOW_FULLSCREEN", WINDOW_FULLSCREEN},
	{"WINDOW_BORDERLESS", WINDOW_BORDERLESS},
	{"WINDOW_RESIZABLE", WINDOW_RESIZABLE},
	{"WINDOW_TITLE", WINDOW_TITLE},
	{"MOUSE_ENABLED", MOUSE_ENABLED},
	{"KEYBOARD_ENABLED", KEYBOARD_ENABLED},
	{"CONTROLLER_ENABLED", CONTROLLER_ENABLED},
	{"MOUSE_SCROLL_SPEED", MOUSE_SCROLL_SPEED},
	{"GENERAL_VOLUME", GENERAL_VOLUME},
	{"MUSIC_VOLUME", MUSIC_VOLUME},
	{"SFX_VOLUME", SFX_VOLUME},
	{"VOICE_VOLUME", VOICE_VOLUME},
	{"AUDIO_TYPE", AUDIO_TYPE},
	{"BRIGHTNESS_LEVEL", BRIGHTNESS_LEVEL},
	{"GAMMA_LEVEL", GAMMA_LEVEL},
	{"CONTRAST_LEVEL", CONTRAST_LEVEL},
	{"VSYNC_ENABLED", VSYNC_ENABLED},
	{"FPS_CAP_LIMIT", FPS_CAP_LIMIT}
});

const std::unordered_map<ConfigID, std::pair<std::string, const std::type_info&>> ResourceManager::sk_configIDMap({
	{PROFILE_NAME, {"PROFILE_NAME", typeid(std::string)}},
	{WINDOW_WIDTH, {"WINDOW_WIDTH", typeid(int)}},
	{WINDOW_HEIGHT, {"WINDOW_HEIGHT", typeid(int)}},
	{WINDOW_FULLSCREEN, {"WINDOW_FULLSCREEN", typeid(int)}},
	{WINDOW_BORDERLESS, {"WINDOW_BORDERLESS", typeid(int)}},
	{WINDOW_RESIZABLE, {"WINDOW_RESIZABLE", typeid(int)}},
	{WINDOW_TITLE, {"WINDOW_TITLE", typeid(std::string)}},
	{MOUSE_ENABLED, {"MOUSE_ENABLED", typeid(int)}},
	{KEYBOARD_ENABLED, {"KEYBOARD_ENABLED", typeid(int)}},
	{CONTROLLER_ENABLED, {"CONTROLLER_ENABLED", typeid(int)}},
	{MOUSE_SCROLL_SPEED, {"MOUSE_SCROLL_SPEED", typeid(int)}},
	{GENERAL_VOLUME, {"GENERAL_VOLUME", typeid(int)}},
	{MUSIC_VOLUME, {"MUSIC_VOLUME", typeid(int)}},
	{SFX_VOLUME, {"SFX_VOLUME", typeid(int)}},
	{VOICE_VOLUME, {"VOICE_VOLUME", typeid(int)}},
	{AUDIO_TYPE, {"AUDIO_TYPE", typeid(int)}},
	{BRIGHTNESS_LEVEL, {"BRIGHTNESS_LEVEL", typeid(int)}},
	{GAMMA_LEVEL, {"GAMMA_LEVEL", typeid(int)}},
	{CONTRAST_LEVEL, {"CONTRAST_LEVEL", typeid(int)}},
	{VSYNC_ENABLED, {"VSYNC_ENABLED", typeid(int)}},
	{FPS_CAP_LIMIT, {"FPS_CAP_LIMIT", typeid(int)}},
});

ResourceManager::ResourceManager() = default;

ResourceManager::ResourceManager(SDL_Renderer* rend) :
	m_renderer(rend)
{

}

ResourceManager::~ResourceManager() {
	saveCurrentConfiguration();
}

void ResourceManager::loadConfig(const std::string& configFilename) {
	fs::path file(configFilename);
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[CONFIGS] / file);

	if (!opt.has_value()) {
		opt = getExistingPath(sk_PATHS[NO_RESTYPE] / file);
		if (!opt.has_value()) {
			throw Inaccessible(configFilename + " could not be found in any of the search paths.");
		}
	}
	m_configFile = opt.value().string();

	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(m_configFile.c_str()) != 0) {
		throw Inaccessible(m_configFile + " could not be loaded properly.");
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("config");
	if (root == nullptr) {
		// File is assumed empty.
		// TODO: Provide a means to generate default configuration.
		return;
	}
	debug << root->GetText();
	
	for (tinyxml2::XMLElement* node = root->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		const std::string name(node->Value());

		if (sk_configStringMap.contains(name)) {
			const ConfigID ID = sk_configStringMap.at(name);
			const std::type_info& type = sk_configIDMap.at(ID).second;
			
			if (type == typeid(int)) {
				configMap.insert_or_assign(ID, std::stoi(std::string(node->GetText())));
			}
			else if (type == typeid(std::string)) {
				configMap.insert_or_assign(ID, std::string(node->GetText()));
			}
		}
	}
}

bool ResourceManager::setConfig(ConfigID id, std::any v) {
	configMap.insert_or_assign(id, v);

	return true;
}

IDtype ResourceManager::loadXML(const std::string& fileName) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[ResourceType::XMLDOC] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + "could not be found in any of the set directory list.");
	}

	std::string file = opt.value().string();
	std::unique_ptr<tinyxml2::XMLDocument> doc = std::make_unique<tinyxml2::XMLDocument>();
	if (doc->LoadFile(file.c_str()) != 0) {
		throw ba::Inaccessible(file + " could not be accessed. Please ensure to have the correct permissions.");
	}
	
	IDtype id = ++xmlDocCount;
	xmlMap[id] = std::move(doc);

	return id;
}

IDtype ResourceManager::loadTexture(const std::string& fileName) {
	std::optional<fs::path> opt = getExistingPath(sk_PATHS[TEXTURES] / fs::path(fileName));

	if (!opt.has_value()) {
		throw std::invalid_argument(fileName + " could not be found in any of the set directory list.");
	}

	fs::path file = opt.value();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(file.string().c_str());

	if (loadedSurface == nullptr) {
		throw std::invalid_argument(IMG_GetError());
	}

	if (m_renderer == nullptr) {
		throw std::logic_error("ResourceManager can't load texture from \"" + file.string() + "\". ResouceManager needs access to a SDL_Renderer.");
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

	Mix_Chunk* newSound = Mix_LoadWAV(file.string().c_str());
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
	Mix_Music* newMusic = Mix_LoadMUS(file.string().c_str());
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
	TTF_Font* newFont = TTF_OpenFont(file.string().c_str(), fontSize);
	if (newFont == NULL) {
		throw std::invalid_argument(TTF_GetError());
	}

	IDtype id = ++fontCount;
	fontsMap.insert_or_assign(id,  newFont);

	return id;
}

std::any ResourceManager::getConfig(ConfigID id) const noexcept {
	if (configMap.contains(id)) {
		return configMap.at(id);
	}

	return std::any();
}

const std::string& ResourceManager::getString(IDtype id) const noexcept {
	if (stringMap.contains(id))
		return stringMap.at(id);

	return stringMap.at(0u);
}

SDL_Texture* ResourceManager::getTexture(IDtype id) const noexcept {
	if(texturesMap.contains(id))
		return texturesMap.at(id);

	return nullptr;
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
	if (fontsMap.contains(id))
		return fontsMap.at(id);
	return NULL;
}

const tinyxml2::XMLDocument* ResourceManager::getXML(IDtype id) const noexcept {
	if (xmlMap.contains(id)) {
		return xmlMap.at(id).get();
	}
	return nullptr;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}


void ResourceManager::addToSearchPaths(const std::string& dir) {
	ResourceManager::addToSearchPaths(fs::path(dir));
}

void ResourceManager::addToSearchPaths(const fs::path& dir) {
	if (dir.has_filename() || !dir.is_absolute() || !fs::exists(dir)) {
		throw std::invalid_argument("ResourceManager::addToSearchPaths() provided argument: \"" + dir.string() + "\" is not a valid path.");
	}

	s_DIRS.push_back(dir);
}

const std::vector<fs::path>& ResourceManager::getBaseDirs() {
	return s_DIRS;
}

std::optional<fs::path> ResourceManager::getExistingPath(const fs::path& suffixPath) {
	for (const fs::path& baseDirectory : s_DIRS) {
		fs::path p(baseDirectory / suffixPath);
		if (fs::exists(p)) {
			return std::make_optional<fs::path>(p);
		}
	}
	return std::nullopt;
}

void ResourceManager::saveCurrentConfiguration() {
	if (m_configFile.empty()) {
		return;
	}
	std::fstream file(m_configFile);
	std::stringstream stream;
	stream << file.rdbuf();
	std::string contents = stream.str();

	// TODO replace rapidxml with anything else.
	// rapidxml::xml_document<> doc;
	// doc.parse<0>(const_cast<char*>(contents.c_str()));
	// rapidxml::xml_node<>* rootNode = doc.first_node("configuration");
	// if (rootNode == nullptr) {
	// 	rootNode = doc.allocate_node(rapidxml::node_element, "configuration");
	// }
	// rapidxml::xml_node<>* node = rootNode->first_node();
	// while(node != nullptr) {
	// 	std::string name(node->name());
	// 	if (sk_configStringMap.contains(name)) {
	// 		const ConfigID ID = sk_configStringMap.at(node->name());
	// 		auto iter = configMap.find(ID);

	// 		if (iter->second.type() == typeid(int)) {
	// 			node->value(std::to_string(std::any_cast<int>(iter->second)).c_str());
	// 		}
	// 		else {
	// 			node->value(std::any_cast<std::string>(iter->second).c_str());
	// 		}
	// 		// TODO: Account for possibility of additional configurations after
	// 		// the loadConfig() method is called (i.e. after the config file is
	// 		// first read.) and write the new configs to the file.
	// 	}
	// 	node = node->next_sibling();
	// }

	// file << doc;
	file.close();
}

} // namespace ba
