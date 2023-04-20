#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>
#include <unordered_map>

#include <BA/Scenes/Scene.hpp>
#include <BA/Types.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class SceneManager {
public:
	SceneManager();

	void handleEvents();
	void update(float deltaTime);
	void postUpdate(float deltaTime);
	void draw(Window& window);

	IDtype add(std::shared_ptr<Scene> scene);
	void remove(IDtype id);

	void switchTo(IDtype id);

	IDtype getCurrentSceneID() const;

private:
	std::unordered_map<IDtype, std::shared_ptr<Scene>> m_scenes;

	IDtype m_currentSceneID{0};
	
	IDtype m_insertedScenes{0};

}; // class SceneManager

} // namespace ba