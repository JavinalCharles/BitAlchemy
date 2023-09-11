#pragma once

#include "BA/Components/Text.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Scenes/Scene.hpp"
#include "BA/Scenes/SceneManager.hpp"
#include "BA/Scenes/SceneManager.hpp"
#include "BA/Systems/EntityManager.hpp"
#include "BA/Systems/MouseControlSystem.hpp"

#include "BA/Tools/DebugHelper.hpp"

namespace ba {

class TextScene : public Scene {
public:
	TextScene();

	TextScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager);

	virtual void handleEvents() override;

	virtual void onCreate() override;
	virtual void onDestroy() override;

	virtual void onActivate() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Window& window) override;

private:
	std::shared_ptr<Text>	m_FPSText = nullptr;

	EntityManager 	m_entityManager;
}; // class TextScene

} // namespace ba
