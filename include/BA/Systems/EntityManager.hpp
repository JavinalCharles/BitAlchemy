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

template <typename T>
concept SystemType = std::is_base_of<ba::ComponentSystem, T>::value;

class EntityManager {
public: // METHODS
	EntityManager();

	~EntityManager();

	void add(std::vector<std::shared_ptr<Entity>> &otherEntities);
	void add(std::shared_ptr<Entity> entity);

	template <SystemType T>
	std::shared_ptr<T> includeSystem();

	template <SystemType T>
	std::shared_ptr<T> getSystem() const;

	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void draw(ba::Window& window);

	void processNewObjects();

	void processRemovals();

	std::shared_ptr<Entity>& operator[](IDtype entityID);
	std::shared_ptr<Entity>& at(IDtype entityID);

private:
	std::map<IDtype, std::shared_ptr<ba::Entity>> m_entities;
	std::vector<std::shared_ptr<ba::Entity>> m_newEntities;

	std::vector<std::shared_ptr<ba::ComponentSystem>> m_componentSystems;

	RenderSystem m_drawables;
}; // class EntityManager


template <SystemType T>
std::shared_ptr<T> EntityManager::includeSystem() {
	for (auto& existingSystem : m_componentSystems) {
		if (std::dynamic_pointer_cast<T>(existingSystem)) {
			return std::dynamic_pointer_cast<T>(existingSystem);
		}
	}

	std::shared_ptr<T> newComponentSystem = std::make_shared<T>(this);
	m_componentSystems.push_back(newComponentSystem);

	return newComponentSystem;
}

template <SystemType T>
std::shared_ptr<T> EntityManager::getSystem() const {
	for (auto& existingSystem : m_componentSystems) {
		if (std::dynamic_pointer_cast<T>(existingSystem)) {
			return std::dynamic_pointer_cast<T>(existingSystem);
		}
	}

	return nullptr;
}


} // namespace ba
