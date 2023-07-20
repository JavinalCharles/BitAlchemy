#pragma once

#include <memory>
#include <set>
#include <vector>
#include <BA/Types.hpp>

namespace ba {

// Forward Declaration
class EntityManager;
class Entity;

class ComponentSystem {
public:
	ComponentSystem(EntityManager* entityManager);

	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);

	virtual void add(std::vector<std::shared_ptr<Entity>>& entities);
	virtual void add(std::shared_ptr<Entity>& entity) = 0;
	virtual void remove(IDtype entityID);

	const std::set<IDtype>& getIDs() const;

protected:
	std::shared_ptr<Entity> getEntity(IDtype id) const;

protected:
	std::set<IDtype> m_entityIDs;

	// Where the actual entities are stored.
	ba::EntityManager* m_entities;

}; // class ComponentSystem

} // namespace ba