#pragma once

#include <cmath>
#include <unordered_set>

#include "BA/Systems/ComponentSystem.hpp"
#include "BA/Components/Colliders/Collider.hpp"
#include "BA/Components/Collidable.hpp"
#include "BA/Components/Velocity.hpp"
#include "BA/Containers/Quadtree.hpp"
#include "BA/Systems/EntityManager.hpp"
#include "BA/Entities/Entity.hpp"
#include "BA/Types.hpp"

namespace ba {

class VelocityWithCollisionSystem : public ComponentSystem {
public:
	explicit VelocityWithCollisionSystem(EntityManager* entityManager);
	virtual ~VelocityWithCollisionSystem();

	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	virtual void add(std::shared_ptr<Entity>& entity) override;

	void addCollisionLayer(IDtype layerID, const std::bitset<128>& collisionBitmask = std::bitset<128>());
	void setCollision(IDtype layerID, IDtype otherLayer);
	void unsetCollision(IDtype layerID, IDtype otherLayer);

	virtual void remove(IDtype entityID) override;

	std::vector<std::shared_ptr<Collider>> searchStatic(const FloatRect& area) const;
	std::vector<std::shared_ptr<Collider>> searchNonStatic(const FloatRect& area) const;
private:
	// HELPER METHODS
	void detectCollisions();
	void resolveCollisions();
	// HELPER HELPER METHODS
	void detectCollisionsForCollider(std::shared_ptr<Collider>& collider);

	void enterCollision(IDtype c1, IDtype c2);

	void useContinuousCollisionDetection(std::shared_ptr<Collider>& collider, const Vector2f& displacement);

	bool checkMostImmediateXRect(const FloatRect& i_BOUNDS, const IDtype& i_LAYER, float xDisplacement);
	bool checkMostImmediateYRect(const FloatRect& i_BOUNDS, const IDtype& i_LAYER, float yDisplacement);

private:
	Quadtree<Collider>	m_staticColliderTree;
	Quadtree<Collider>	m_objectsColliderTree;

	std::unordered_map<unsigned, std::bitset<128>> m_collisionLayers;

	std::vector<std::pair<IDtype, IDtype>> m_collisions;

	std::unordered_set<IDtype>	m_nonCollidingEntityIDs;
}; // class VelocityWithCollisionSystem

} // namespace ba
