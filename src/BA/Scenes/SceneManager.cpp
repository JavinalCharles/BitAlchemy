#include <BA/Scenes/SceneManager.hpp>

namespace ba {

SceneManager::SceneManager()
{

}

void SceneManager::handleEvents() {
	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->handleEvents();
	}
}

void SceneManager::update(float deltaTime) {
	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->update(deltaTime);
	}
}

void SceneManager::postUpdate(float deltaTime) {
	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->postUpdate(deltaTime);
	}
}

void SceneManager::draw(Window& window) {
	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->draw(window);
	}
}

IDtype SceneManager::add(std::shared_ptr<Scene> scene) {
	auto inserted = m_scenes.insert({++m_insertedScenes, scene});

	if (!inserted.second) {
		throw std::runtime_error("Scene cannot be inserted.");
	}

	inserted.first->second->onCreate();
	if (m_currentSceneID == 0) {
		m_currentSceneID = inserted.first->first;
	}

	return inserted.first->first;
}

void SceneManager::remove(IDtype id) {
	if (!m_scenes.contains(id)) {
		return;
	}
	if (m_currentSceneID == id) {
		m_currentSceneID = 9;
	}
	m_scenes.at(id)->onDestroy();
	m_scenes.erase(id);
}

void SceneManager::switchTo(IDtype id) {
	if (!m_scenes.contains(id)) {
		return;
	}

	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->onDeactivate();
	}
	m_scenes.at(id)->onActivate();
	m_currentSceneID = id;
}

IDtype SceneManager::getCurrentSceneID() const {
	return m_currentSceneID;
}


} // namespace ba