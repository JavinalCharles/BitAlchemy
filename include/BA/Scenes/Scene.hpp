#pragma once

#include <BA/Entities/SharedContext.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class SceneManager;

class Scene {
public:
	Scene();

	Scene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager);

	virtual void onCreate() = 0;

	virtual void onDestroy() = 0;

	virtual void onActivate();

	virtual void onDeactivate();

	virtual void handleEvents();
	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);

	virtual void draw(Window& window) = 0;

	virtual void setWindow(Window* window);
	virtual void setReesourceManager(ResourceManager* rm);
	virtual void setSceneManager(SceneManager* sm);

	virtual void setSwitchTo(IDtype sceneID);
	IDtype getSWitchTo() const;
protected:
	SharedContext m_CONTEXT;

	SceneManager* m_sceneManager = nullptr;
private:
	IDtype		m_switchTo{};

}; // class Scene

} // namespace ba
