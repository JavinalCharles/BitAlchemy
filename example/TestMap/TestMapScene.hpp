#pragma once

#include <BA/Components/Sprite.hpp>
#include <BA/Scenes/Scene.hpp>
#include <BA/Systems/EntityManager.hpp>
#include <BA/Generator/TileMapGenerator.hpp>

#include <BA/Tools/DebugHelper.hpp>

namespace ba {

class TestMapScene : public Scene {
public:
	TestMapScene();
	TestMapScene(Window* window, ResourceManager* ResourceManager, SceneManager* sceneManager);

	virtual void onCreate();
	virtual void onDestroy();

	virtual void onActivate() override;

	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;
	virtual void draw(Window& window);
private:
	generator::TileMapGenerator m_mapGenerator; 

	EntityManager m_entityManager;
}; // class TestMapScene

} // namespace ba
