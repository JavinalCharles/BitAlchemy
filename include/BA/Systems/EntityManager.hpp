#pragma once

#include <map>
#include <memory>
#include <vector>
#include <set>
#include <stdexcept>
#include "BA/Entities/Entity.hpp"
#include "BA/Systems/ComponentSystem.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class EntityManager {
public: // METHODS
	~EntityManager();

	void add(std::vector<std::shared_ptr<ba::Entity>> &otherEntities);
	void add(std::shared_ptr<ba::Entity> entity);

	template <typename T>
	void includeSystem();

	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void draw(ba::Window& window);

	void processNewObjects();

	void processRemovals();

	std::shared_ptr<ba::Entity>& operator[](unsigned entityID);

private:
	std::map<unsigned, std::shared_ptr<ba::Entity>> m_entities;
	std::vector<std::shared_ptr<ba::Entity>> m_newEntities;

	// TEMPORARY until RenderSystem is created.
	std::set<unsigned> m_drawables;

	std::vector<std::shared_ptr<ba::ComponentSystem>> m_componentSystems;
}; // class EntityManager


template <typename T>
void EntityManager::includeSystem() {
	static_assert(std::is_base_of<ba::ComponentSystem, T>::value, "Error. EntityManager::includeSystem<T>(). T must be a derived type of ba::ComponentSystem. Assertion returned false.");

	for (auto& existingSystem : m_componentSystems) {
		if (std::dynamic_pointer_cast<T>(existingSystem)) {
			return;
		}
	}

	std::shared_ptr<T> newComponentSystem = std::make_shared<T>(this);
	m_componentSystems.push_back(newComponentSystem);
}


} // namespace ba