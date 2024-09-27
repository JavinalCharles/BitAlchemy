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
		std::cout << "\rRendering scene ID: " << m_currentSceneID << std::flush;
		m_scenes.at(m_currentSceneID)->draw(window);
	}
}

IDtype SceneManager::add(std::shared_ptr<Scene> scene) {
	auto inserted = m_scenes.insert({++m_insertedScenes, scene});

	if (!inserted.second) {
		throw std::runtime_error("Scene cannot be inserted.");
	}

	inserted.first->second->create();
	if (m_currentSceneID == 0) {
		this->switchTo(inserted.first->first);
	}

	return inserted.first->first;
}

void SceneManager::remove(IDtype id) {
	if (!m_scenes.contains(id)) {
		return;
	}
	if (m_currentSceneID == id) {
		m_currentSceneID = 0;
	}
	m_scenes.at(id)->destroy();
	m_scenes.erase(id);
}

void SceneManager::switchTo(IDtype id) {
	if (!m_scenes.contains(id)) {
		return;
	}

	if (m_currentSceneID != 0) {
		m_scenes.at(m_currentSceneID)->deactivate();
	}
	m_scenes.at(id)->activate();
	m_currentSceneID = id;
}

IDtype SceneManager::getCurrentSceneID() const {
	return m_currentSceneID;
}


} // namespace ba
