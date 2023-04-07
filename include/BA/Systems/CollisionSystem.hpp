#pragma once 

#include <bitset>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <BA/Components/Colliders/Collider.hpp>
#include <BA/Containers/Quadtree.hpp>
#include <BA/Entities/Entity.hpp>
#include <BA/Types.hpp>

namespace ba {

class CollisionSystem {
public:
	CollisionSystem(EntityManager* entities);

	~CollisionSystem();

	void add(std::vector<std::shared_ptr<Entity>>& entities);
	void add(std::shared_ptr<Entity>& entity);

	void remove(IDtype entityID);

	void update(float deltaTime);

	void addCollisionLayer(unsigned layer, const std::bitset<127>& collisionBitmask = std::bitset<127>());
	void setCollision(unsigned layer, unsigned otherLayer);
	void unsetCollision(unsigned layer, unsigned otherLayer);

private:
	void detectCollisions();
	void processCollisions();
	void resolveCollisions();

private:
	Quadtree<Collider>	m_staticColliderTree;

	std::unordered_map<unsigned, std::bitset<127>> m_collisionLayers;

	std::vector<std::pair<IDtype, IDtype>> m_collisions;

	std::unordered_set<IDtype> m_IDs;

	EntityManager* m_entities;
}; // class CollisionSystem

} // namespace ba