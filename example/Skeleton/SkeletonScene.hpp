#include <iostream>

#include <BA/Scenes/Scene.hpp>
#include <BA/Components/Text.hpp>
#include <BA/Inputs/MouseInput.hpp>
#include <BA/Systems/AISystem.hpp>
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/SoundSystem.hpp>
#include <BA/Systems/TimerSystem.hpp>

#include <BA/Tools/DebugHelper.hpp>

#include "BlueCharEntity.hpp"
#include "SkeletonEntity.hpp"

namespace ba {

using ba::Resources::Warehouse;

class SkeletonScene : public Scene {
public:
	SkeletonScene();
	SkeletonScene(Window* window, Warehouse* warehouse, SceneManager* sceneManager);

	virtual void onCreate() override;
	virtual void onDestroy() override;

	virtual void onActivate() override;

	virtual void handleEvents() override;
	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	virtual void draw(Window& window);

private:
	void createSkeleton();

private:
	std::shared_ptr<Text>	m_FPSText;

	std::shared_ptr<MouseInput>	m_mouseInput = nullptr;

	EntityManager	m_entityManager;
	InputManager 	m_inputManager;
	MusicPlayer 	m_musicPlayer;
}; // class SkeletonScene


} // namespace ba
