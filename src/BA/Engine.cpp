#include <BA/Engine.hpp>


namespace ba {

Engine::Engine() :
	m_window(),
	m_entities(),
	m_resources(nullptr),
	m_inputs(),
	m_context{&m_entities, &m_resources, &m_window, &m_inputs}
{

}

Engine::Engine(const std::string& title, IntRect dimension, std::uint32_t winFlags) :
	m_window(title, dimension.l, dimension.t, dimension.w, dimension.h, winFlags),
	m_entities(),
	m_resources(nullptr),
	m_inputs(),
	m_context{&m_entities, &m_resources, &m_window, &m_inputs}
{

}

void Engine::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		throw std::runtime_error(IMG_GetError());
	}
	if(TTF_Init() < 0) {
		throw std::runtime_error(TTF_GetError());
	}

	m_window.init();
	m_resources.setRenderer(m_window.getRenderer());
}

void Engine::run() {
	const float FPS = 1000.f / 60.f;

	std::uint64_t NOW = SDL_GetTicks64();
	std::uint64_t LAST = 0;
	std::uint64_t elapsedTime = 0;

	do {
		LAST = NOW;
		NOW = SDL_GetTicks64();

		elapsedTime = NOW - LAST;
		while(elapsedTime < FPS) {
			NOW = SDL_GetTicks64();
			elapsedTime = NOW - LAST;
		}

		float deltaTime = elapsedTime / 1000.f;

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
	m_inputs.handleEvents();
}

void Engine::update(float deltaTime) {
	m_entities.update(deltaTime);
}

void Engine::postUpdate(float deltaTime) {
	m_entities.postUpdate(deltaTime);
}

void Engine::draw() {
	m_window.clear();
	m_entities.draw(m_window);
	m_window.display();
}

SharedContext* Engine::getContext(){
	return &m_context;
}

void Engine::cleanUp() {
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

}; // namespace ba