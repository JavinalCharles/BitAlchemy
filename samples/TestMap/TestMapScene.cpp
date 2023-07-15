#include "TestMapScene.hpp"

#include <iostream>

using std::filesystem::path;

namespace ba {

TestMapScene::TestMapScene() :
	Scene::Scene()
{
	m_CONTEXT.entities = &m_entityManager;
}

TestMapScene::TestMapScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) :
	Scene::Scene(window, resourceManager, sceneManager)
{
	m_CONTEXT.entities = &m_entityManager;
}

void TestMapScene::onCreate() {

}

void TestMapScene::onDestroy() {

}

void TestMapScene::onActivate() {
	const Vector2f SCALE{1.5f, 1.5f};
	path p = m_CONTEXT.resources->getBaseDirectory() / path("Textures") / path("oak_woods_tileset.tsx");

	TileSet tiles = generateTileSet(1, p.string(), m_CONTEXT.resources);

	std::clog << "Generated " << tiles.size() << " tiles." << std::endl;

	std::vector<std::shared_ptr<Entity>> entities;

	std::clog << "Creating entities." << std::endl;
	for (auto& [k, v] : tiles) {
		std::shared_ptr<Entity> e = std::make_shared<Entity>(&m_CONTEXT);
		e->setScale(SCALE);
		e->setPosition({v.textureRect.l * SCALE.x, v.textureRect.t * SCALE.y});
		std::shared_ptr<Sprite> sprite = e->addComponent<Sprite>();
		sprite->setTexture(v.textureID);
		sprite->setTextureRect(v.textureRect);

		entities.push_back(e);
	}
	std::clog << "Adding new entities to the game." << std::endl;
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