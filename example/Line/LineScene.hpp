#pragma once

#include <memory>

#include "BA/Components/Text.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Inputs/MouseInput.hpp"
#include "BA/Scenes/Scene.hpp"
#include "BA/Scenes/SceneManager.hpp"
#include "BA/Systems/EntityManager.hpp"
#include "BA/Systems/MouseControlSystem.hpp"
#include "BA/Utilities/Line.hpp"

#include "BA/Tools/DebugHelper.hpp"

namespace ba {

class LineScene : public Scene {
public:
	LineScene();

	LineScene(Window* window, ResourceManager* resourceManager, SceneManager* SceneManager);

	virtual void onCreate() override;
	virtual void onDestroy() override;

	virtual void onActivate() override;

	virtual void handleEvents() override;

	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	virtual void draw(Window& window);
private:
	std::shared_ptr<Text>	m_FPSText = nullptr;

	std::weak_ptr<MouseInput> m_mouseInput;

	EntityManager 	m_entityManager;
	InputManager	m_inputManager;

	static const Vector2i sk_CENTER;
}; // class LineScene

} // naemspace ba
