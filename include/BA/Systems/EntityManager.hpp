#pragma once

#include <map>
#include <memory>
#include <vector>
#include <set>
#include <stdexcept>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/CollisionSystem.hpp>
#include <BA/Systems/ComponentSystem.hpp>
#include <BA/Systems/RenderSystem.hpp>
#include <BA/Types.hpp>
#include <BA/Window/Window.hpp>

namespace ba {

class EntityManager {
public: // METHODS
	EntityManager();

	~EntityManager();

	void add(std::vector<std::shared_ptr<Entity>> &otherEntities);
	void add(std::shared_ptr<Entity> entity);

	template <typename System>
	std::shared_ptr<System> includeSystem();

	template <typename System>
	std::shared_ptr<System> getSystem() const;

	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void draw(ba::Window& window);

	void processNewObjects();

	void processRemovals();

	std::shared_ptr<Entity>& operator[](IDtype entityID);
	std::shared_ptr<Entity>& at(IDtype entityID);

private:
	std::map<unsigned, std::shared_ptr<ba::Entity>> m_entities;
	std::vector<std::shared_ptr<ba::Entity>> m_newEntities;

	std::vector<std::shared_ptr<ba::ComponentSystem>> m_componentSystems;
	RenderSystem m_drawables;
}; // class EntityManager


template <typename System>
std::shared_ptr<System> EntityManager::includeSystem() {
	static_assert(std::is_base_of<ba::ComponentSystem, System>::value, "Error. EntityManager::includeSystem<T>(). T must be a derived type of ba::ComponentSystem. Assertion returned false.");

	for (auto& existingSystem : m_componentSystems) {
		if (std::dynamic_pointer_cast<System>(existingSystem)) {
			return std::dynamic_pointer_cast<System>(existingSystem);
		}
	}

	std::shared_ptr<System> newComponentSystem = std::make_shared<System>(this);
	m_componentSystems.push_back(newComponentSystem);

	return newComponentSystem;
}

template <typename System>
std::shared_ptr<System> EntityManager::getSystem() const {
	static_assert(std::is_base_of<ba::ComponentSystem, System>::value, "Error. EntityManager::getSystem<T>(). T must be a derived type of ba::ComponentSystem. Assertion returned false.");

	for (auto& existingSystem : m_componentSystems) {
		if (std::dynamic_pointer_cast<System>(existingSystem)) {
			return std::dynamic_pointer_cast<System>(existingSystem);
		}
	}

	return nullptr;
}


} // namespace ba