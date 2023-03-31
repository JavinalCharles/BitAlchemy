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
	float NOW = SDL_GetPerformanceCounter();
	float LAST = 0.f;

	do {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		float deltaTime = static_cast<float>((NOW - LAST)*1000 / static_cast<float>(SDL_GetPerformanceFrequency()));
		this->handleEvents();

		if (m_window.isOpen()) {
			this->update(deltaTime);
			this->postUpdate(deltaTime);
			this->draw();
		}
		SDL_Delay(std::floor(16.666f - deltaTime));

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

void Engine::cleanUp() {
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

}; // namespace ba