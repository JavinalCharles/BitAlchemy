#include <BA/Systems/CollisionSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

#include <iostream>

namespace ba {

CollisionSystem::CollisionSystem(EntityManager* entities) :
	ComponentSystem(entities),
	m_staticColliderTree(15, 8, 0, ba::FloatRect{0, 0, 9600, 4600}),
	m_objectsColliderTree(15, 8, 0, ba::FloatRect{0, 0, 9000, 4600})
{

}

CollisionSystem::~CollisionSystem() {
	m_staticColliderTree.clear();
	m_objectsColliderTree.clear();
	m_collisionLayers.clear();
}

void CollisionSystem::add(std::shared_ptr<Entity>& entity) {
	auto collider = entity->getCollider();
	if(collider == nullptr)
		return;
	if(entity->isStatic()) {
		m_staticColliderTree.insert(collider);
	}
	else {
		this->addID(entity->ID);
	}
	if (!m_collisionLayers.contains(collider->getLayer())) {
		this->addCollisionLayer(collider->getLayer());
	}
}

void CollisionSystem::remove(IDtype entityID) {
	if(m_entityIDs.contains(entityID)) {
		m_entityIDs.erase(entityID);
		return;
	}
	m_staticColliderTree.remove(m_entities->at(entityID)->getCollider());
}

void CollisionSystem::update(float) {
	
}

void CollisionSystem::postUpdate(float) {
	m_objectsColliderTree.clear();
	for (const IDtype& ID: getIDs()) {
		auto collider = getEntity(ID)->getCollider();
		m_objectsColliderTree.insert(collider);
	}
	detectCollisions();
	processCollisions();
	resolveCollisions();
}

void CollisionSystem::addCollisionLayer(IDtype layer, const std::bitset<128>& collisionBitmask) {
	m_collisionLayers.insert_or_assign(layer, collisionBitmask);
}

void CollisionSystem::setCollision(IDtype layer, IDtype otherLayer) {
	if(!m_collisionLayers.contains(layer)) {
		addCollisionLayer(layer);
	}
	m_collisionLayers.at(layer).set(otherLayer);
}

void CollisionSystem::unsetCollision(IDtype layer, IDtype otherLayer) {
	if(!m_collisionLayers.contains(layer)) {
		addCollisionLayer(layer);
	}
	m_collisionLayers.at(layer).set(otherLayer, false);
}

std::vector<std::shared_ptr<Collider>> CollisionSystem::searchStatic(const FloatRect& area) const {
	return m_staticColliderTree.search(area);
}

std::vector<std::shared_ptr<Collider>> CollisionSystem::searchNonStatic(const FloatRect& area) const {
	return m_objectsColliderTree.search(area);
}

void CollisionSystem::detectCollisions() {
	for(IDtype ID : m_entityIDs) {
		auto i_collider = m_entities->at(ID)->getCollider();
		unsigned i_layer = i_collider->getLayer();

		// Check for collision with static objects;
		auto staticSearched = m_staticColliderTree.search(i_collider->getGlobalBounds());
		for(auto& j_collider : staticSearched) {
			unsigned j_layer = j_collider->getLayer();
			if(m_collisionLayers.at(i_layer)[j_layer]) {
				if(i_collider->isColliding(j_collider)) {
					this->enterCollision(ID, j_collider->getOwner()->ID);
				}	
			}
		} // end for each j_collider

		// Check for collision with non-static objects;
		auto nonStaticSearched = m_objectsColliderTree.search(i_collider->getGlobalBounds());
		for(auto& k_collider : nonStaticSearched) {
			if (i_collider->getOwner()->ID == k_collider->getOwner()->ID) {
				continue;	// Same object. Proceed to next iteration of this loop.
			}
			const unsigned k_layer = k_collider->getLayer();
			if (m_collisionLayers.at(i_layer).test(k_layer)) {
				if(i_collider->isColliding(k_collider)) {
					this->enterCollision(ID, k_collider->getOwner()->ID);
				}
			}
		} // end for each k_collider
	} // end for each ID
}

void CollisionSystem::processCollisions() {
	// TODO: Collision Behaviors
	for (auto& p : m_collisions) {
		auto p1_collidable = getEntity(p.first)->getComponent<Collidable>();
		auto p2_collidable = getEntity(p.second)->getComponent<Collidable>();
		if (p1_collidable != nullptr) {
			p1_collidable->onCollisionStay(p.second);
		}
		if (p2_collidable != nullptr) {
			p2_collidable->onCollisionStay(p.first);
		}
	}
}

namespace {
	Vector2f measureDisplacement(const FloatRect& r1, const FloatRect& r2) {
		float xDiff = (r1.l + (r1.w * 0.5f)) - (r2.l + (r2.w * 0.5f));
		float yDiff = (r1.t + (r1.h * 0.5f)) - (r2.t + (r2.h * 0.5f));

		if(std::fabs(xDiff) > std::fabs(yDiff)){
			return Vector2f {
				(xDiff > 0) ? ((r2.l + r2.w) - r1.l) + 1.f : -((r1.l + r1.w) - r2.l) - 1.f,
				0.f
			};
		}
		else {
			return Vector2f {
				0.f,
				(yDiff > 0) ? ((r2.t + r2.h) - r1.t) + 1.f : -((r1.t + r1.h) - r2.t) - 1.f
			};
		}
			
	}
}

void CollisionSystem::resolveCollisions() {
	for(auto& collision : m_collisions) {
		auto i_collider = m_entities->at(collision.first)->getCollider();
		auto j_collider = m_entities->at(collision.second)->getCollider();

		const bool iStatic = i_collider->getOwner()->isStatic();
		const bool jStatic = j_collider->getOwner()->isStatic();

		if(!iStatic && jStatic) {
			FloatRect j_bounds = j_collider->getGlobalBounds();
			while (i_collider->isColliding(j_collider)) {
				FloatRect i_bounds = i_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = i_bounds.intersects(j_bounds);
				if (!intersection.has_value()) {
					break;
				}
				i_collider->resolve(measureDisplacement(i_bounds, j_bounds));
			}
		}
		else if (iStatic && !jStatic) {
			FloatRect i_bounds = j_collider->getGlobalBounds();
			while(j_collider->isColliding(i_collider)) {
				FloatRect j_bounds = i_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = j_bounds.intersects(i_bounds);
				if (!intersection.has_value()) {
					break;
				}
				j_collider->resolve(measureDisplacement(j_bounds, i_bounds));
			}
		}
		else if (!iStatic && !jStatic) {
			while(i_collider->isColliding(j_collider)) {
				FloatRect i_bounds = i_collider->getGlobalBounds();
				FloatRect j_bounds = j_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = i_bounds.intersects(j_bounds);
				if (!intersection.has_value()) {
					break;
				}
				i_collider->resolve(measureDisplacement(i_bounds, j_bounds) * 0.5f);
				j_collider->resolve(measureDisplacement(j_bounds, i_bounds) * 0.5f);
			}
		}

		auto p1_collidable = getEntity(collision.first)->getComponent<Collidable>();
		auto p2_collidable = getEntity(collision.second)->getComponent<Collidable>();
		if (p1_collidable != nullptr) {
			p1_collidable->onCollisionExit(collision.second);
		}
		if (p2_collidable != nullptr) {
			p2_collidable->onCollisionExit(collision.first);
		}

	}

	m_collisions.clear();
}

void CollisionSystem::enterCollision(IDtype c1, IDtype c2) {
	m_collisions.push_back(std::make_pair(c1, c2));
	auto c1_collidable = getEntity(c1)->getComponent<Collidable>();
	auto c2_collidable = getEntity(c2)->getComponent<Collidable>();
	if (c1_collidable != nullptr) {
		c1_collidable->onCollisionEnter(c2);
	}
	if (c2_collidable != nullptr) {
		c2_collidable->onCollisionEnter(c1);
	}
}

} // namespace ba