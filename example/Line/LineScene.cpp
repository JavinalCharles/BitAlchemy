#include "LineScene.hpp"

namespace ba {

const Vector2i LineScene::sk_CENTER(256, 256);

LineScene::LineScene() :
	Scene::Scene()
{
	m_CONTEXT.entities = &m_entityManager;
	m_CONTEXT.inputs = &m_inputManager;
}

LineScene::LineScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene::Scene(window, resourceManager, sceneManager)
{
	m_CONTEXT.entities = &m_entityManager;
	m_CONTEXT.inputs = &m_inputManager;
}

void LineScene::onCreate() {
	m_mouseInput = m_CONTEXT.inputs->addInput<MouseInput>();

	m_entityManager.includeSystem<ba::MouseControlSystem>();
}

void LineScene::onDestroy() {
	m_FPSText.reset();
}

void LineScene::onActivate() {
	std::shared_ptr<Entity> fpsEntity = std::make_shared<Entity>(&m_CONTEXT);
	fpsEntity->setPosition({5.f, 5.f});
	m_FPSText = fpsEntity->addComponent<Text>();
	m_FPSText->loadFontFromFile("UbuntuMono-Bold.ttf", 16);
	m_FPSText->setColor(Color::Blue);

	std::shared_ptr<Entity> angleEntity = std::make_shared<Entity>(&m_CONTEXT);
	angleEntity->setPosition({256.f, 5.f});
	m_angleText = angleEntity->addComponent<Text>();
	m_angleText->setFontID(m_FPSText->getFontID());
	m_angleText->setColor(Color::Yellow);


	m_entityManager.add(fpsEntity);
	m_entityManager.add(angleEntity);

	debug.setColor(Color::White);
}

void LineScene::handleEvents() {
	m_inputManager.handleEvents();
}

void LineScene::update(float deltaTime) {
	int fps = static_cast<int>(std::round(1.0f / deltaTime));
	m_FPSText->setText(std::to_string(fps) + " FPS");

	m_entityManager.update(deltaTime);

	if (m_mouseInput.expired()) {
		ba::debug << "Mouse Input has expired.\n";
		return;
	}

	std::shared_ptr<MouseInput> mi = m_mouseInput.lock();
	const Vector2i mousePos(mi->getCurrMousePos());

	IntLine line(sk_CENTER, mousePos);

	m_angleText->setText(std::to_string(line.angle().wrapUnsigned().asDegrees()) + " Degrees");

	ba::debug << line;
}

void LineScene::postUpdate(float deltaTime) {
	m_entityManager.postUpdate(deltaTime);
}

void LineScene::draw(Window& window) {
	m_entityManager.draw(window);
}


} // namespace ba
