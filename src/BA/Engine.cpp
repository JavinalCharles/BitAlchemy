#include <BA/Engine.hpp>


namespace ba {

Engine::Engine() :
	m_window(),
	m_resources(nullptr)

{

}

Engine::Engine(const std::string& title, IntRect dimension, std::uint32_t winFlags) :
	m_window(title, dimension.l, dimension.t, dimension.w, dimension.h, winFlags),
	m_resources(nullptr)
{

}

void Engine::setFPSLimit(uint16 fps) {
	m_fpsLimit = fps;
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
