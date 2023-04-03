#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <BA/Components/Colliders/BoxCollider.hpp>
#include <BA/Components/Sprite.hpp>
#include <BA/Engine.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Entities/SharedContext.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Window/Window.hpp>
#include <BA/Utilities/Color.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Utilities/Vector2.hpp>

class Game : public ba::Engine {
public:
	Game();

	virtual void init() override;
};

Game::Game()
	: ba::Engine()
{

}

void Game::init() {
	Engine::init();

	m_entities.includeSystem<ba::KeyboardControlSystem>();
	m_entities.includeSystem<ba::MovementSystem>();

	std::shared_ptr<ba::Entity> entity = std::make_shared<ba::Entity>(&m_context);

	auto sprite = entity->addComponent<ba::Sprite>();
	sprite->loadTextureFromFile("./player.png");
	entity->setPosition({64.f, 64.f});
	ba::FloatRect bounds = sprite->getLocalBounds();
	entity->setOrigin({bounds.w/2.f, bounds.h/2.f});

	auto collider = entity->addComponent<ba::BoxCollider>();
	collider->setLayer(1u);
	collider->setSize({bounds.w, bounds.h});

	auto velocity = entity->addComponent<ba::Velocity>();
	velocity->setMax({480.f, 480.f});
	std::cout << "Entity Max Velocity set: { " << velocity->getMax().x << ", " << velocity->getMax().y << " };\n";

	auto keyControl = entity->addComponent<ba::KeyboardControl>();
	keyControl->bindOnKeyActive(SDLK_w, std::bind(&ba::Velocity::moveUp, velocity.get()));
	keyControl->bindOnKeyActive(SDLK_a, std::bind(&ba::Velocity::moveLeft, velocity.get()));
	keyControl->bindOnKeyActive(SDLK_s, std::bind(&ba::Velocity::moveDown, velocity.get()));
	keyControl->bindOnKeyActive(SDLK_d, std::bind(&ba::Velocity::moveRight, velocity.get()));

	std::shared_ptr<ba::Entity> ball = std::make_shared<ba::Entity>(&m_context);
	ball->setStatic(true);

	auto ballSprite = ball->addComponent<ba::Sprite>();
	ballSprite->loadTextureFromFile("./ball.png");
	ball->setPosition({224, 320});
	ba::FloatRect ballBounds = ballSprite->getLocalBounds();
	ball->setOrigin({ballBounds.w*0.5f, ballBounds.h*0.5f});

	auto ballCollider = ball->addComponent<ba::BoxCollider>();
	ballCollider->setLayer(1u);
	ballCollider->setSize({ballBounds.w, ballBounds.h});

	m_entities.add(entity);
	m_entities.add(ball);	
}


int main() {
	Game game;

	game.init();
	
	game.run();

	game.cleanUp();

	return 0;
}