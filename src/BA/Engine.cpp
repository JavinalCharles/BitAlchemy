#include <BA/Engine.hpp>


namespace ba {

Engine::Engine()
{

}

Engine::Engine(const std::string& orgName, const std::string& appName)
{
	char* prefPath = SDL_GetPrefPath(orgName.c_str(), appName.c_str());
	if (prefPath == nullptr) {
		throw ba::Inaccessible(SDL_GetError());
	}

	m_resources.addToSearchPaths(std::string(prefPath));
}

Engine::Engine(const std::string& organization, const std::string& title, const IntRect& dimension, ba::uint32 windowFlags) :
	m_window(organization + "|" + title, dimension, windowFlags),
	m_resources(nullptr)
{
	// TODO: Add organization and title to Resources configs
	char* prefPath = SDL_GetPrefPath(organization.c_str(), title.c_str());

	if (prefPath == nullptr) {
		return;
	}
	std::string p(prefPath);
	m_resources.addToSearchPaths(p);
	SDL_free(prefPath);

}

Engine::Engine(const std::string& title, const IntRect& dimension, ba::uint32 winFlags) :
	m_window(title, dimension, winFlags),
	m_resources(nullptr)
{
	char* prefPath = SDL_GetPrefPath(nullptr, title.c_str());

	if (prefPath == nullptr) {
		return;
	}
	std::string p(prefPath);
	m_resources.addToSearchPaths(p);
	SDL_free(prefPath);
}

void Engine::setFPSLimit(uint16 fps) {
	m_fpsLimit = fps;
}

Window& Engine::getWindow() {
	return m_window;
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
	m_resources.setRenderer(m_window.getRenderer());

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
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

}; // namespace ba
