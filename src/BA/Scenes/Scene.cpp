#include <BA/Scenes/Scene.hpp>
#include <BA/Scenes/SceneManager.hpp>

namespace ba {

Scene::Scene() = default;

Scene::Scene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager) {
	setWindow(window);
	setReesourceManager(resourceManager);
	setSceneManager(sceneManager);
}

void Scene::onActivate()
{

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

void Scene::setReesourceManager(ResourceManager* resourceManager) {
	m_CONTEXT.resources = resourceManager;
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