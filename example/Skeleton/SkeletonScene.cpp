#include "SkeletonScene.hpp"

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
	m_mouseInput = m_CONTEXT.inputs->addInput<MouseInput>();
	m_CONTEXT.inputs->addInput<KeyboardInput>();

	m_entityManager.includeSystem<AISystem>();
	m_entityManager.includeSystem<AnimationSystem>();
	m_entityManager.includeSystem<KeyboardControlSystem>();
	m_entityManager.includeSystem<MovementSystem>();
	m_entityManager.includeSystem<SoundSystem>();
	// m_entityManager.includeSystem<TimerSystem>();
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

	debug.setColor(Color::Blue);
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

	m_entityManager.update(deltaTime);

	if (m_mouseInput->isButtonDown(MouseButton::LEFT)) {
		Vector2i pos = m_mouseInput->getCurrMousePos();
		ba::debug << "Left Mouse Button Clicked: {" << pos.x << ", " << pos.y << " }\n";
	}

	if (m_mouseInput->isButtonDown(MouseButton::MIDDLE)) {
		Vector2i pos = m_mouseInput->getCurrMousePos();
		ba::debug << "Middle Mouse Button Clicked: {" << pos.x << ", " << pos.y << " }\n";
	}

	if (m_mouseInput->isButtonDown(MouseButton::RIGHT)) {
		Vector2i pos = m_mouseInput->getCurrMousePos();
		ba::debug << "Right Mouse Button Clicked: {" << pos.x << ", " << pos.y << " }\n";
	}

	Vector2i pos = m_mouseInput->getCurrMousePos();
	IntRect rect{
		64 * (pos.x / 64),
		64 * (pos.y / 64),
		64,
		64
	};
	ba::debug << rect << static_cast<Vector2f>(pos);

	// window.drawRect(rect);

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
	std::shared_ptr<BlueCharEntity> blueChar = std::make_shared<BlueCharEntity>(&m_CONTEXT);

	m_entityManager.add(skeleton);
	m_entityManager.add(blueChar);
}

} // namespace ba
