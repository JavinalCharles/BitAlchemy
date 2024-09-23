#include <BA/Engine.hpp>


namespace ba {

SDL_Renderer* globalRenderer = nullptr;

Engine::Engine()
{
	__construct();
}

Engine::Engine(const std::string& orgName, const std::string& appName)
{
	__construct(orgName, appName);
}

Engine::Engine(const std::string& organization, const std::string& title, const IntRect& dimension, ba::uint32 windowFlags) :
	m_window(organization + "|" + title, dimension, windowFlags)
{
	__construct(organization, title);
}

Engine::Engine(const std::string& orgName, const std::string& appName, const std::string& configFileName) {
	__construct(orgName, appName);

	m_resources.loadConfig(configFileName);
}

Engine::Engine(const std::string& title, const IntRect& dimension, ba::uint32 winFlags) :
	m_window(title, dimension, winFlags)
{
	__construct("", title);
}

void Engine::__construct(const std::string& org, const std::string& app) {
	m_resources.setConfig(ORG_NAME, org);
	m_resources.setConfig(APP_NAME, app);

	char* prefPath = SDL_GetPrefPath(org.c_str(), app.c_str());
	if (prefPath != nullptr) {
		debug << "Adding " << prefPath << " to search paths." << std::endl;
		m_resources.addToSearchPaths(fs::path(prefPath));
	}
	else {
		debug << "Prefered Path could not be determined." << std::endl;
	}
	char* basePath = SDL_GetBasePath();
	if (basePath != nullptr) {
		debug << "Adding " << basePath << " to search paths." << std::endl;
		m_resources.addToSearchPaths(fs::path(basePath));
	}
	else {
		debug << "Base Path could not be determined." << std::endl;
	}

	SDL_free(prefPath);
	SDL_free(basePath);
}

void Engine::setFPSLimit(uint16 fps) {
	m_fpsLimit = fps;
}

Window& Engine::getWindow() {
	return m_window;
}

ResourceManager& Engine::getResourceManager() {
	return m_resources;
}

void Engine::setWindowSize(int w, int h) {
	m_window.setSize(w, h);
}

void Engine::setWindowSize(const Vector2i& size) {
	m_window.setSize(size);
}

void Engine::setWindowDimension(int x, int y, int w, int h) {
	m_window.setDimension(x, y, w, h);
}

void Engine::setWindowDimension(const Vector2i& pos, const Vector2i& size) {
	m_window.setDimension(pos, size);
}

void Engine::setWindowDimension(const IntRect& dimension) {
	m_window.setDimension(dimension);
}

void Engine::setWindowFlags(uint32 flags) {
	m_window.setFlags(flags);
}

void Engine::addWindowFlags(uint32 flags) {
	m_window.addFlags(flags);
}

uint16 Engine::getFPSLimit() const {
	return m_fpsLimit;
}

void Engine::init() {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		throw std::runtime_error(IMG_GetError());
	}
	int audioInit = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	if (audioInit != 0) {
		throw std::runtime_error(Mix_GetError());
	}
	if(TTF_Init() < 0) {
		throw std::runtime_error(TTF_GetError());
	}

	m_window.init();

	// m_resources.setRenderer(m_window.getRenderer());

	this->onInit();

	for (auto& initFunc : m_initFunctions) {
		initFunc();
	}
}

void Engine::onInit() {

}

void Engine::onInit(const std::function<void()>& initFunc) {
	m_initFunctions.push_back(initFunc);
}

IDtype Engine::addScene(std::shared_ptr<Scene> scene) {
	return m_sceneManager.add(scene);
}

void Engine::run() {
	const std::uint64_t COUNTS_PER_SECOND = SDL_GetPerformanceFrequency();
	const float COUNTS_PER_FRAME = COUNTS_PER_SECOND / static_cast<float>(m_fpsLimit);

	std::uint64_t NOW = SDL_GetPerformanceCounter();
	std::uint64_t LAST = 0;
	std::uint64_t elapsedTime = 0;

	do {
		LAST = NOW;
		do {
			NOW = SDL_GetPerformanceCounter();
			elapsedTime = NOW - LAST;
		} while(elapsedTime < COUNTS_PER_FRAME);

		float deltaTime = elapsedTime / static_cast<float>(COUNTS_PER_SECOND);

		this->handleEvents();

		if (m_window.isOpen()) {
			this->update(deltaTime);
			this->postUpdate(deltaTime);
			this->draw();
		}

	} while(m_window.isOpen());
}

void Engine::handleEvents() {
	SDL_PumpEvents();
	m_window.handleEvents();
	m_sceneManager.handleEvents();
}

void Engine::update(float deltaTime) {
	m_sceneManager.update(deltaTime);
}

void Engine::postUpdate(float deltaTime) {
	m_sceneManager.postUpdate(deltaTime);
}

void Engine::draw() {
	m_window.clear();
	m_sceneManager.draw(m_window);

	ba::debug.draw(m_window);

	m_window.display();
}

void Engine::cleanUp() {
	m_resources.freeAllResources();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

}; // namespace ba
