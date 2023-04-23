#include <iostream>

#include <BA/Scenes/Scene.hpp>
#include <BA/Components/Text.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Systems/AnimationSystem.hpp>
#include <BA/Systems/KeyboardControlSystem.hpp>
#include <BA/Systems/MovementSystem.hpp>
#include <BA/Systems/SoundSystem.hpp>

#include "SkeletonEntity.hpp"

namespace ba {

class SkeletonScene : public Scene {
public:
	SkeletonScene();
	SkeletonScene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager);

	virtual void onCreate();
	virtual void onDestroy();

	virtual void onActivate() override;

	virtual void handleEvents() override;
	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	virtual void draw(Window& window);

private:
	void createSkeleton();

private:
	std::shared_ptr<Text>	m_FPSText;

	EntityManager	m_entityManager;
	InputManager 	m_inputManager;
	MusicPlayer 	m_musicPlayer;

}; // class SkeletonScene


} // namespace ba