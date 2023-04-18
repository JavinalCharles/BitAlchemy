#pragma once 

#include <cmath>
#include <memory>
#include <map>
#include <utility>
#include <vector>
#include <BA/Components/Colliders/Collider.hpp>
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

	void remove(IDtype entityID);

	void postUpdate(float deltaTime);

	void addCollisionLayer(IDtype layerID, const std::bitset<128>& collisionBitmask = std::bitset<128>());
	void setCollision(IDtype layerID, IDtype otherLayer);
	void unsetCollision(IDtype layerID, IDtype otherLayer);

private:
	void detectCollisions();
	void processCollisions();
	void resolveCollisions();

private:
	Quadtree<Collider>	m_staticColliderTree;

	std::unordered_map<unsigned, std::bitset<128>> m_collisionLayers;

	std::vector<std::pair<IDtype, IDtype>> m_collisions;
}; // class CollisionSystem

} // namespace ba