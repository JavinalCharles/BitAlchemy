#include <BA/Scenes/SceneManager.hpp>

namespace ba {

SceneManager::SceneManager()
{

}

void SceneManager::handleEvents() {
	if (!m_sceneStack.empty()) {
		m_scenes.at(m_sceneStack.back())->handleEvents();
	}
}

void SceneManager::update(float deltaTime) {
	if (!m_sceneStack.empty()) {
		m_scenes.at(m_sceneStack.back())->update(deltaTime);
	}
}

void SceneManager::postUpdate(float deltaTime) {
	if (!m_sceneStack.empty()) {
		m_scenes.at(m_sceneStack.back())->postUpdate(deltaTime);
	}
}

void SceneManager::draw(Window& window) {
	if (!m_sceneStack.empty()) {
		m_scenes.at(m_sceneStack.back())->draw(window);
	}
}

void SceneManager::switchToScene(const std::type_index& index) {
	if (m_scenes.contains(index)) {
		m_sceneStack.push_back(index);
		m_scenes.at(index)->activate();
	}
}

void SceneManager::removeScene(const std::type_index& sceneIndex) {
	if (!m_scenes.contains(sceneIndex)) {
		return;
	}
	for (const std::type_index& index : m_sceneStack) {
		if (index == sceneIndex) {
			// SceneIndex is still in stack. Ignore.
			return;
		}
	}
	m_scenes.at(sceneIndex)->destroy();
	m_scenes.erase(sceneIndex);
}

std::shared_ptr<Scene> SceneManager::getCurrentScene() const {
	if (m_sceneStack.empty()) {
		return nullptr;
	}
	return m_scenes.at(m_sceneStack.back());
}

void SceneManager::popSceneStack() {
	if (m_sceneStack.empty()) {
		return;
	}
	std::type_index index(m_sceneStack.back());
	m_scenes.at(index)->deactivate();
	m_scenes.at(index)->destroy();
	m_sceneStack.pop_back();

	if (m_sceneStack.empty()) {
		return;
	}
	m_scenes.at(m_sceneStack.back())->activate();
}


} // namespace ba
