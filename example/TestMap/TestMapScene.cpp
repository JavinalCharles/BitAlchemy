#include "TestMapScene.hpp"

using std::filesystem::path;

namespace ba {

namespace fs = std::filesystem;
namespace res = ba::Resources;

using ba::debug;


TestMapScene::TestMapScene() :
	Scene::Scene()
{
	m_CONTEXT.entities = &m_entityManager;
}

TestMapScene::TestMapScene(Window* window, Warehouse* warehouse, SceneManager* sceneManager) :
	Scene::Scene(window, warehouse, sceneManager),
	m_mapGenerator(&m_CONTEXT)
{
	m_CONTEXT.entities = &m_entityManager;
}

void TestMapScene::onCreate() {
	res::TextureManager& textures = m_CONTEXT.warehouse->includeResourceManager<res::TextureManager>();
	textures.addPath(fs::path("Textures"));

	res::XMLManager& xmls = m_CONTEXT.warehouse->includeResourceManager<res::XMLManager>();
	xmls.addPath(fs::path("XML"));
}

void TestMapScene::onDestroy() {

}

void TestMapScene::onActivate() {
	const Vector2f SCALE{1.5f, 1.5f};
	std::string fileName = "classroom.tmx";

	ba::debug << "Generating Map Entities." << std::endl;
	m_entities = m_mapGenerator.generate(fileName, SCALE);
	ba::debug << "Generated total " << m_entities.size() << " entities." << std::endl;

	// ba::debug << "Adding new entities to the game." << std::endl;
	m_CONTEXT.entities->add(m_entities);
}

void TestMapScene::update(float deltaTime) {
	m_CONTEXT.entities->update(deltaTime);
}

void TestMapScene::postUpdate(float deltaTime) {
	m_CONTEXT.entities->postUpdate(deltaTime);
}

void TestMapScene::draw(Window& window) {
	m_CONTEXT.entities->draw(window);
	// for (auto& entity : m_entities) {
	// 	auto drawable = entity->getDrawable();
	// 	if (drawable != nullptr) {
	// 		drawable->draw(window);
	// 	}
	// }
}

} // namespace ba
