#pragma once

#include <vector>
#include <functional>

#include <BA/Entities/Entity.hpp>
#include <BA/Entities/SharedContext.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class SceneManager;

template<typename E>
concept EntityType = std::is_base_of<ba::Entity, E>::value;

class Scene {
public:
	Scene();

	Scene(Window* window, ResourceManager* resourceManager, SceneManager* sceneManager);

	void create();
	void destroy();
	void activate();
	void deactivate();

	std::shared_ptr<Entity> createEntity();
	template <EntityType T>
	std::shared_ptr<T> createCustomEntity();

	virtual void onCreate();
	virtual void onCreate(const std::function<void()>& function);
	virtual void onDestroy();

	virtual void onActivate();
	virtual void onActivate(const std::function<void()>& function);
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

	std::vector<std::function<void()>> m_onCreateFunctions;
	std::vector<std::function<void()>> m_onActivateFunctions;
}; // class Scene

/**
 * BELOW ARE METHOD IMPLEMETATIONS
**/
template <EntityType T>
std::shared_ptr<T> Scene::createCustomEntity() {
	return std::make_shared<T>(&m_CONTEXT);
}

} // namespace ba
