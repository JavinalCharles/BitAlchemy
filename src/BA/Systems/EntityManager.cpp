#include "BA/Systems/EntityManager.hpp"

namespace ba {

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
}

void EntityManager::postUpdate(float deltaTime) {
	for (auto& system : m_componentSystems) {
		system->postUpdate(deltaTime);
	}
	processRemovals();
}

void EntityManager::draw(ba::Window& window) {
	// TEMPORARY until a dedicated RenderSystem is created.
	for (unsigned eID : m_drawables) {
		auto drawable = m_entities[eID]->getDrawable();
		drawable->draw(window);
	}
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

		if (e->getDrawable() != nullptr) {
			m_drawables.insert(ID);
		}

		for (auto& system: m_componentSystems) {
			system->addEntity(e);
		}
	}

	m_newEntities.clear();
}

void EntityManager::processRemovals() {
	// TODO
}

std::shared_ptr<ba::Entity>& EntityManager::operator[](unsigned entityID) {
	if (!m_entities.contains(entityID)) {
		throw std::out_of_range("No entity exists with such ID: " + entityID);
	}

	return m_entities.at(entityID);
}

} // namespace ba