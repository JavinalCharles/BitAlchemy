#include "SkeletonScene.hpp"

#include <iostream>

namespace ba {

SkeletonScene::SkeletonScene() :
	Scene::Scene(),
	m_musicPlayer(nullptr)
{
	m_CONTEXT.entities = &m_entityManager;
	m_CONTEXT.inputs = &m_inputManager;
	m_CONTEXT.player = &m_musicPlayer;
}

SkeletonScene::SkeletonScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene::Scene(window, resourceManager, sceneManager),
	m_musicPlayer(resourceManager)
{
	m_CONTEXT.entities = &m_entityManager;
	m_CONTEXT.inputs = &m_inputManager;
	m_CONTEXT.player = &m_musicPlayer;


}

void SkeletonScene::onCreate() {
	m_CONTEXT.inputs->addInput<KeyboardInput>();

	m_entityManager.includeSystem<AnimationSystem>();
	m_entityManager.includeSystem<KeyboardControlSystem>();
	m_entityManager.includeSystem<MovementSystem>();
	m_entityManager.includeSystem<SoundSystem>();
}

void SkeletonScene::onActivate() {
	m_musicPlayer.addMusic("Patreon Goal Reward Loops - Track 01.wav");
	m_musicPlayer.setLooping(true);

	m_musicPlayer.play();
	createSkeleton();

	std::shared_ptr<Entity> fpsEntity = std::make_shared<Entity>(&m_CONTEXT);
	fpsEntity->setPosition({5.f, 5.f});

	m_FPSText = fpsEntity->addComponent<Text>();
	m_FPSText->loadFontFromFile("UbuntuMono-Bold.ttf", 16);
	m_FPSText->setColor(Color::Blue);

	m_entityManager.add(fpsEntity);
}

void SkeletonScene::onDestroy() {
	m_musicPlayer.clearMusicList();
	// TODO
}

void SkeletonScene::handleEvents() {
	m_inputManager.handleEvents();
}

void SkeletonScene::update(float deltaTime) {
	m_musicPlayer.update();
	int fps = static_cast<int>(std::round(1.0f / deltaTime));
	m_FPSText->setText(std::to_string(fps) + " FPS");

	// std::clog << "Text: " << m_FPSText->getText() << std::endl;
	m_entityManager.update(deltaTime);
	
}

void SkeletonScene::postUpdate(float deltaTime) {
	m_entityManager.postUpdate(deltaTime);
}

void SkeletonScene::draw(Window& window) {
	m_entityManager.draw(window);
	// m_FPSText->draw(window);
}

void SkeletonScene::createSkeleton() {
	std::shared_ptr<SkeletonEntity> skeleton = std::make_shared<SkeletonEntity>(&m_CONTEXT);

	m_entityManager.add(skeleton);
}

} // namespace ba