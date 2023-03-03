#pragma once

#include <memory>
#include <set>

namespace ba {

// Forward Declaration
class EntityManager;
class Entity;

class ComponentSystem {
public:
	ComponentSystem(ba::EntityManager* entityManager);

	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);

	virtual void add(std::shared_ptr<ba::Entity>& entity) = 0;
	virtual void remove(unsigned entityID);

protected:
	std::set<unsigned> m_entityIDs;

	// Where the actual entities are stored.
	ba::EntityManager* m_entities;

}; // class ComponentSystem

} // namespace ba