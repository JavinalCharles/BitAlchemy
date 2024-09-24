#include <BA/Scenes/Scene.hpp>
#include <BA/Scenes/SceneManager.hpp>

namespace ba {

using ba::Resources::Warehouse;

Scene::Scene() = default;

Scene::Scene(Window* window, Warehouse* warehouse, SceneManager* sceneManager) {
	setWindow(window);
	setWarehouse(warehouse);
	setSceneManager(sceneManager);
}

void Scene::create() {
	this->onCreate();

	for (auto& createFunc : m_onCreateFunctions) {
		createFunc();
	}
}

void Scene::activate() {
	this->onActivate();

	for (auto& activateFunc : m_onActivateFunctions) {
		activateFunc();
	}
}

void Scene::destroy() {
	this->onDestroy();
}

void Scene::deactivate() {
	this->onDeactivate();
}

std::shared_ptr<Entity> Scene::createEntity() {
	return std::make_shared<Entity>(&m_CONTEXT);
}

void Scene::onCreate() {

}

void Scene::onCreate(const std::function<void()>& func) {
	m_onCreateFunctions.push_back(func);
}

void Scene::onActivate() {

}

void Scene::onActivate(const std::function<void()>& func) {
	m_onActivateFunctions.push_back(func);
}

void Scene::onDestroy() {

}

void Scene::onDeactivate()
{

}

void Scene::handleEvents()
{

}

void Scene::update(float)
{

}

void Scene::postUpdate(float)
{

}

void Scene::setWindow(Window* window) {
	m_CONTEXT.window = window;
}

void Scene::setWarehouse(Warehouse* warehouse) {
	m_CONTEXT.warehouse = warehouse;
}

void Scene::setSceneManager(SceneManager* sceneManager) {
	m_sceneManager = sceneManager;
}

void Scene::setSwitchTo(IDtype sceneID) {
	m_switchTo = sceneID;
}

IDtype Scene::getSWitchTo() const {
	return m_switchTo;
}
} // namespace ba
