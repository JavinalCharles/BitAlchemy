#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <BA/Components/Sprite.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Entities/SharedContext.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Window/Window.hpp>
#include <BA/Utilities/Color.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Utilities/Vector2.hpp>

namespace {
	int init() {
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "SDL cannot be initialized. Got Error: " << SDL_GetError() << std::endl;
			return -1;
		}
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if(!(IMG_Init(imgFlags) & imgFlags)) {
			std::cout << "SDL_image cannot be initialized. Caught Error: " << IMG_GetError() << std::endl;
			return -2;
		}

		if(TTF_Init() < 0) {
			std::cout << "SDL_ttf cannot be innitialized. Caught Error: " << TTF_GetError() << std::endl;
		}
		std::cout << "SDL initialized successfully." << std::endl;
		return 0;
	}

	int close() {
		// TTF_Quit();
		IMG_Quit();
		SDL_Quit();

		return 0;
	}
}
	

int main() {
	bool initialized = (init() == 0);
	if (!initialized) {
		std::cout << "SDL Initialization returned with an error. Terminating Program." << std::endl;
		return -1;
	}


	ba::EntityManager entityManager;
	ba::Window gameWindow("FEATHER GAME ENGINE - TEST RUN");
	ba::ResourceManager resources(gameWindow.getRenderer());

	ba::SharedContext context{
		&entityManager,
		&resources,
		&gameWindow
	};

	std::shared_ptr<ba::Entity> entity = std::make_shared<ba::Entity>(&context);

	
	auto sprite = entity->addComponent<ba::Sprite>();
	sprite->loadTextureFromFile("./player.png");
	entity->setPosition({64, 64});
	ba::FloatRect bounds = sprite->getLocalBounds();
	entity->setOrigin({bounds.w / 2.f, bounds.h / 2.f});


	std::shared_ptr<ba::Entity> ball = std::make_shared<ba::Entity>(&context);
	auto ballSprite = ball->addComponent<ba::Sprite>();
	ballSprite->loadTextureFromFile("./ball.png");
	ball->setPosition({200, 300});

	entityManager.add(entity);
	entityManager.add(ball);
	// START GAME LOOP

	std::uint64_t NOW = SDL_GetPerformanceCounter();
	std::uint64_t LAST = 0;
	float deltaTime = 0;
	
	do {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = static_cast<float>((NOW - LAST)*1000 / static_cast<float>(SDL_GetPerformanceFrequency()));

		// Handle Events
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gameWindow.close();
			}
			else if (e.type == SDL_KEYDOWN) {
				ba::View view = gameWindow.getView();
				switch(e.key.keysym.sym) {
					case SDLK_a:
						view.move({-64.f * deltaTime, 0});
						break;
					case SDLK_w:
						view.move({0, -64.f * deltaTime});
						break;
					case SDLK_s:
						view.move({0, 64 * deltaTime});
						break;
					case SDLK_d:
						view.move({64 * deltaTime, 0});
						break;
				}
				gameWindow.setView(view);
			}
		}

		if (gameWindow.isOpen()) {
			entityManager.update(deltaTime);
			entityManager.postUpdate(deltaTime);
			gameWindow.clear(ba::Color::White);
			entityManager.draw(gameWindow);
			gameWindow.display();
		}

	} while(gameWindow.isOpen());


	return close();
}