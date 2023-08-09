#pragma once 

#include <bitset>
#include <cmath>
#include <memory>
#include <map>
#include <utility>
#include <vector>
#include <BA/Components/Colliders/Collider.hpp>
#include <BA/Components/Colliders/BoxCollider.hpp>
#include <BA/Components/Collidable.hpp>
#include <BA/Containers/Quadtree.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Systems/ComponentSystem.hpp>
#include <BA/Types.hpp>

namespace ba {

class CollisionSystem : public ComponentSystem {
public:
	CollisionSystem(EntityManager* entities);

	~CollisionSystem();

	virtual void add(std::shared_ptr<Entity>& entity);
	virtual void remove(IDtype entityID) override;

	virtual void update(float deltaTime) override;
	virtual void postUpdate(float deltaTime) override;

	void addCollisionLayer(IDtype layerID, const std::bitset<128>& collisionBitmask = std::bitset<128>());
	void setCollision(IDtype layerID, IDtype otherLayer);
	void unsetCollision(IDtype layerID, IDtype otherLayer);

	std::vector<std::shared_ptr<Collider>> searchStatic(const FloatRect& area) const;
	std::vector<std::shared_ptr<Collider>> searchNonStatic(const FloatRect& area) const;

private:
	void detectCollisions();
	void processCollisions();
	void resolveCollisions();

	void enterCollision(IDtype c1, IDtype c2);

private:
	Quadtree<Collider>	m_staticColliderTree;
	Quadtree<Collider>	m_objectsColliderTree;

	std::unordered_map<unsigned, std::bitset<128>> m_collisionLayers;

	std::vector<std::pair<IDtype, IDtype>> m_collisions;
}; // class CollisionSystem

} // namespace ba