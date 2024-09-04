#include "TestMapScene.hpp"

using std::filesystem::path;

namespace ba {

TestMapScene::TestMapScene() :
	Scene::Scene()
{
	m_CONTEXT.entities = &m_entityManager;
}

TestMapScene::TestMapScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene::Scene(window, resourceManager, sceneManager),
	m_mapGenerator(&m_CONTEXT)
{
	m_CONTEXT.entities = &m_entityManager;
}

void TestMapScene::onCreate() {

}

void TestMapScene::onDestroy() {

}

void TestMapScene::onActivate() {
	const Vector2f SCALE{1.5f, 1.5f};
	std::string fileName = "classroom.tmx";

	ba::debug << "Generating Map Entities." << std::endl;
	std::vector<std::shared_ptr<Entity>> entities = m_mapGenerator.generate(fileName, SCALE);
	ba::debug << "Generated total " << entities.size() << " entities." << std::endl;

	ba::debug << "Adding new entities to the game." << std::endl;
	m_CONTEXT.entities->add(entities);
}

void TestMapScene::update(float deltaTime) {
	m_CONTEXT.entities->update(deltaTime);
}

void TestMapScene::postUpdate(float deltaTime) {
	m_CONTEXT.entities->postUpdate(deltaTime);
}

void TestMapScene::draw(Window& window) {
	m_CONTEXT.entities->draw(window);
}

} // namespace ba
