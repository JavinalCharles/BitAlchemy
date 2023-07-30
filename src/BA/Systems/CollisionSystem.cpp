#include <BA/Systems/CollisionSystem.hpp>
#include <BA/Systems/EntityManager.hpp>

#include <iostream>

namespace ba {

CollisionSystem::CollisionSystem(EntityManager* entities) :
	ComponentSystem(entities),
	m_staticColliderTree(15, 8, 0, ba::FloatRect{0, 0, 9600, 4600})
{

}

CollisionSystem::~CollisionSystem() {
	m_staticColliderTree.clear();
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
		this->m_entityIDs.insert(entity->ID);
	}
}

void CollisionSystem::remove(IDtype entityID) {
	if(m_entityIDs.contains(entityID)) {
		m_entityIDs.erase(entityID);
		return;
	}
	m_staticColliderTree.remove(m_entities->at(entityID)->getCollider());
}

void CollisionSystem::postUpdate(float) {
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

void CollisionSystem::detectCollisions() {
	for(IDtype ID : m_entityIDs) {
		auto i_collider = m_entities->at(ID)->getCollider();
		unsigned i_layer = i_collider->getLayer();
		auto staticSearched = m_staticColliderTree.search(i_collider->getGlobalBounds());
		for(auto& j_collider : staticSearched) {
			unsigned j_layer = j_collider->getLayer();
			if(m_collisionLayers.at(i_layer)[j_layer]) {
				if(i_collider->isColliding(j_collider)) {
					m_collisions.push_back(std::make_pair(ID, j_collider->getOwner()->ID));
				}	
			}
		}

		for(IDtype j_ID : m_entityIDs) {
			if (j_ID == ID) continue;

			auto j_collider = m_entities->at(j_ID)->getCollider();
			unsigned j_layer = j_collider->getLayer();
			if(m_collisionLayers.at(i_layer)[j_layer]) {
				if(i_collider->isColliding(j_collider)) {
					m_collisions.push_back(std::make_pair(ID, j_collider->getOwner()->ID));
				}
			}
		}
	}
}

void CollisionSystem::processCollisions() {
	// TODO: Collision Behaviors
}

namespace {
	Vector2f measureDisplacement(const FloatRect& r1, const FloatRect& r2) {
		float xDiff = (r1.l + (r1.w * 0.5f)) - (r2.l + (r2.w * 0.5f));
		float yDiff = (r1.t + (r1.h * 0.5f)) - (r2.t + (r2.h * 0.5f));

		if(std::fabs(xDiff) > std::fabs(yDiff)){
			return Vector2f {
				(xDiff > 0) ? ((r2.l + r2.w) - r1.l) : -((r1.l + r1.w) - r2.l),
				0.f
			};
		}
		else {
			return Vector2f {
				0.f,
				(yDiff > 0) ? ((r2.t + r2.h) - r1.t) : -((r1.t + r1.h) - r2.t)
			};
		}
	}
}

void CollisionSystem::resolveCollisions() {
	for(auto& collision : m_collisions) {
		auto i_collider = m_entities->at(collision.first)->getCollider();
		auto j_collider = m_entities->at(collision.second)->getCollider();

		FloatRect iBounds = i_collider->getGlobalBounds();
		FloatRect jBounds = j_collider->getGlobalBounds();

		std::optional<FloatRect> rect = iBounds.intersects(jBounds);

		if(!rect.has_value())
			continue;
		const bool iStatic = i_collider->getOwner()->isStatic();
		const bool jStatic = j_collider->getOwner()->isStatic();

		if(!iStatic && jStatic) {
			// std::clog << "non-static vs static" << std::endl;
			i_collider->getOwner()->move(measureDisplacement(iBounds, rect.value()));
		}
		else if (iStatic && !jStatic) {
			// std::clog << "static vs non-static" << std::endl;
			j_collider->getOwner()->move(measureDisplacement(jBounds, rect.value()));
		}
		else if (!iStatic && !jStatic) {
			std::clog << "static vs static" << std::endl;
			i_collider->getOwner()->move(measureDisplacement(iBounds, rect.value()) * 0.5f);
			j_collider->getOwner()->move(measureDisplacement(jBounds, rect.value()) * 0.5f);
		}
	}

	m_collisions.clear();
}

} // namespace ba