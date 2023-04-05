#include "BA/Systems/EntityManager.hpp"
#include <iostream>

namespace ba {

EntityManager::EntityManager() :
	m_drawables(this),
	m_colliders(this)
{
	m_colliders.addCollisionLayer(1u);
	m_colliders.setCollision(1u, 1u);
}

EntityManager::~EntityManager() {
	m_entities.clear();
	m_newEntities.clear();
}

void EntityManager::add(std::vector<std::shared_ptr<ba::Entity>>& newEntities) {
	m_newEntities.insert(m_newEntities.end(), newEntities.begin(), newEntities.end());
}

void EntityManager::add(std::shared_ptr<ba::Entity> entity) {
	m_newEntities.push_back(entity);
}

void EntityManager::update(float deltaTime) {
	processNewObjects();
	for (auto& system : m_componentSystems) {
		system->update(deltaTime);
	}
	m_drawables.update(deltaTime);
	m_colliders.update(deltaTime);
}

void EntityManager::postUpdate(float deltaTime) {
	for (auto& system : m_componentSystems) {
		system->postUpdate(deltaTime);
	}
	processRemovals();
}

void EntityManager::draw(ba::Window& window) {
	m_drawables.draw(window);
}

void EntityManager::processNewObjects() {
	if (m_newEntities.size() <= 0) {
		// No new objects. terminate function.
		return;
	}

	for (auto& e: m_newEntities) {
		e->awake();

		const unsigned ID = e->ID;
		m_entities.insert_or_assign(ID, e);

		m_drawables.add(e);
		m_colliders.add(e);

		for (auto& system: m_componentSystems) {
			system->add(e);
		}
	}

	m_newEntities.clear();
}

void EntityManager::processRemovals() {
	auto iter = m_entities.begin();
	while(iter != m_entities.end()) {
		if(iter->second->isQueuedForRemoval()) {
			m_drawables.remove(iter->first);
			m_colliders.remove(iter->first);
			for(auto& componentSystem : m_componentSystems) {
				componentSystem->remove(iter->first);
			}

			iter = m_entities.erase(iter);
		}
		else {
			++iter;
		}
	}
}

std::shared_ptr<ba::Entity>& EntityManager::operator[](unsigned entityID) {
	// if (!m_entities.contains(entityID)) {
	// 	throw std::out_of_range("No entity exists with such ID: " + entityID);
	// }
	return m_entities.at(entityID);
}

std::shared_ptr<ba::Entity>& EntityManager::at(unsigned entityID) {
	return m_entities.at(entityID);
}

} // namespace ba