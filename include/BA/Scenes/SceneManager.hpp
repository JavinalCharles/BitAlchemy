#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <type_traits>

#include <BA/Scenes/Scene.hpp>
#include <BA/Types.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

template <typename S>
concept SceneType = std::is_base_of_v<Scene, S>;


/**
 * @brief Where all scene objects are stored and managed.
 * 
 */
class SceneManager {
public:
	/**
	 * @brief Construct a new Scene Manager object
	 * 
	 */
	SceneManager();

	/**
	 * @brief Delegates the event handling to the currently active 
	 * scene
	 * 
	 */
	void handleEvents();
	/**
	 * @brief Delegates the update task to the currently active scene.
	 * 
	 * @param deltaTime time since last frame
	 */
	void update(float deltaTime);
	/**
	 * @brief Same as update.
	 * 
	 * @param deltaTime time since last frame
	 */
	void postUpdate(float deltaTime);
	/**
	 * @brief Delegates the rendering process to the currently active
	 * scene.
	 * 
	 * @param window 
	 */
	void draw(Window& window);

	/**
	 * @brief Create a Scene object
	 * 
	 * @tparam S 
	 * @param window the window
	 * @param warehouse the warehouse
	 * @return a pair object with the type_index from typeid(S) and a
	 * pointer to the created scene.
	 */
	template<SceneType S>
	std::pair<std::type_index, std::shared_ptr<S>> createScene(Window* window, Resources::Warehouse* warehouse);

	/**
	 * @brief Pushes a scene mapped by index to the scene stack.
	 * 
	 * Does nothing if no scene mapped by index was created
	 * beforehand.
	 * 
	 * @param index the index to the desired scene
	 */
	void switchToScene(const std::type_index& index);

	/**
	 * @brief Removes a scene that is created earlier.
	 * 
	 * Does nothing if a scene of sceneIndex does not exists, or if it
	 * still exists within the stack (Even if the scene is not the
	 * currently active scene).
	 * 
	 * @param sceneIndex the index to the scene.
	 */
	void removeScene(const std::type_index& sceneIndex);

	/**
	 * @brief Get the Current Scene object
	 * 
	 * @return A pointer to the currently active scene.
	 */
	std::shared_ptr<Scene> getCurrentScene() const;

	/**
	 * @brief Pops the top of the scene stack.
	 * 
	 * If the stack is not empty after pop, then the new scene at the
	 * top of the stack will be the new currently active scene.
	 * 
	 */
	void popSceneStack();

private:
	std::unordered_map<std::type_index, std::shared_ptr<Scene>> m_scenes;

	std::vector<std::type_index> m_sceneStack;

}; // class SceneManager

template <SceneType S>
std::pair<std::type_index, std::shared_ptr<S>> SceneManager::createScene(Window* window, Resources::Warehouse* warehouse) {
	std::type_index index(typeid(S));

	if (!m_scenes.contains(index)) {
		m_scenes.insert_or_assign(index, std::make_shared<S>(window, warehouse, this));
		// m_scenes.at(index)->create();
	}

	return std::make_pair(index, std::dynamic_pointer_cast<S>(m_scenes.at(index)));
}


} // namespace ba