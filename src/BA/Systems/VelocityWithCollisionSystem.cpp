#include "BA/Systems/VelocityWithCollisionSystem.hpp"

#include <iostream>

namespace ba {

VelocityWithCollisionSystem::VelocityWithCollisionSystem(EntityManager* entityManager) :
	ComponentSystem::ComponentSystem(entityManager),
	m_staticColliderTree(15, 8, 0, ba::FloatRect{0, 0, 9600, 4600}),
	m_objectsColliderTree(15, 8, 0, ba::FloatRect{0, 0, 9000, 4600})
{

}

VelocityWithCollisionSystem::~VelocityWithCollisionSystem() {
	m_staticColliderTree.clear();
	m_objectsColliderTree.clear();
	m_collisionLayers.clear();
	m_collisions.clear();
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

	FloatRect get1PixelXDisplacementRect(const FloatRect& rect, float xDisplacement) {
		FloatRect result{
			rect.l, rect.t, 1.f, rect.h
		};
		if (xDisplacement < 0.f) {
			result.l = std::trunc(rect.l - 1.f);
		}
		else {
			result.l = std::trunc(rect.l + rect.w + 1);
		}
		return result;
		
	}
	FloatRect get1PixelYDisplacementRect(const FloatRect& rect, float yDisplacement) {
		FloatRect result{
			rect.l, rect.t, rect.w, 1.f
		};
		if (yDisplacement < 0.f) {
			result.t = std::trunc(rect.t - 1.f);
		}
		else {
			result.t = std::trunc(rect.t + rect.h + 1.f);
		}
		return result;
	}
} // Anonymous namespace

void VelocityWithCollisionSystem::update(float deltaTime) {
	for (const IDtype& ID : m_nonCollidingEntityIDs) {
		auto e = getEntity(ID);
		e->move(e->getComponent<Velocity>()->get() * deltaTime);
	}

	for (const IDtype& ID : getIDs()) {
		auto e = getEntity(ID);
		auto velocity = e->getComponent<Velocity>();
		auto i_collider = e->getCollider();
		const unsigned i_LAYER = i_collider->getLayer();
		const FloatRect i_BOUNDS = i_collider->getGlobalBounds();

		Vector2f displacement = velocity->get() * deltaTime;
		if (displacement.x != 0.f) {
			FloatRect xBound = get1PixelXDisplacementRect(i_BOUNDS, displacement.x);
			auto staticCollisions = m_staticColliderTree.search(xBound);
			for (auto& j_collider : staticCollisions) {
				const unsigned j_LAYER = j_collider->getLayer();
				if (m_collisionLayers.at(i_LAYER).test(j_LAYER)) {
					displacement.x = 0.f;
					break;
				}
			}
		}
		if (displacement.y != 0.f) {
			FloatRect yBound = get1PixelYDisplacementRect(i_BOUNDS, displacement.y);
			auto staticCollisions = m_staticColliderTree.search(yBound);
			for (auto& k_collider : staticCollisions) {
				const unsigned k_LAYER = k_collider->getLayer();
				if (m_collisionLayers.at(i_LAYER).test(k_LAYER)) {
					displacement.y = 0.f;
					break;
				}
			}
		}

		e->move(displacement);
	}

	m_objectsColliderTree.clear();
	for (const IDtype& ID : getIDs()) {
		auto collider = getEntity(ID)->getCollider();
		m_objectsColliderTree.insert(collider);
	}
}

void VelocityWithCollisionSystem::postUpdate(float) {
	// std::clog << "VelocityWithCollisionSystem::postUpdate()\n";
	detectCollisions();
	resolveCollisions();
}

void VelocityWithCollisionSystem::add(std::shared_ptr<Entity>& entity) {
	auto collider = entity->getCollider();
	auto velocity = entity->getComponent<Velocity>();
	if (collider == nullptr && velocity == nullptr) {
		return;
	}


	if (collider != nullptr) {
		if (velocity == nullptr || entity->isStatic()) {
			// Entity has collider, but no velocity
			// Treat as static collider
			// std::clog << "Entity with collider but no velocity, found. ID: #" << entity->ID << std::endl; 
			m_staticColliderTree.insert(collider);
		}
		else {
			// std::clog << "Entity with collider and velocity, found. ID: #" << entity->ID << std::endl; 
			m_objectsColliderTree.insert(collider);
			this->addID(entity->ID);
		}
		if (!m_collisionLayers.contains(collider->getLayer())) {
			this->addCollisionLayer(collider->getLayer());
		}
	}
	else if (velocity != nullptr && collider == nullptr) {
		// No collider but with velocity
		// std::clog << "Entity with velocity but no collider, found. ID: #" << entity->ID << std::endl;
		m_nonCollidingEntityIDs.insert(entity->ID);
	}
}

void VelocityWithCollisionSystem::addCollisionLayer(IDtype layerID, const std::bitset<128>& collisionBitmask) {
	m_collisionLayers.insert_or_assign(layerID, collisionBitmask);
}

void VelocityWithCollisionSystem::setCollision(IDtype layerID, IDtype otherLayer) {
	if(!m_collisionLayers.contains(layerID)) {
		addCollisionLayer(layerID);
	}
	m_collisionLayers.at(layerID).set(otherLayer, true);
}

void VelocityWithCollisionSystem::unsetCollision(IDtype layerID, IDtype otherLayer) {
	if(!m_collisionLayers.contains(layerID)) {
		addCollisionLayer(layerID);
	}
	m_collisionLayers.at(layerID).set(otherLayer, false);
}

void VelocityWithCollisionSystem::detectCollisions() {
	for (const IDtype& ID : getIDs()) {
		auto i_collider = m_entities->at(ID)->getCollider();
		// const unsigned i_LAYER = i_collider->getLayer();

		detectCollisionsForCollider(i_collider);
	}
}

void VelocityWithCollisionSystem::resolveCollisions() {
	for (auto& collisions : m_collisions) {
		auto p1_collidable = getEntity(collisions.first)->getComponent<Collidable>();
		auto p2_collidable = getEntity(collisions.second)->getComponent<Collidable>();

		if (p1_collidable != nullptr) {
			p1_collidable->onCollisionStay(collisions.second);
		}
		if (p2_collidable != nullptr) {
			p2_collidable->onCollisionStay(collisions.first);
		}


		auto i_collider = getEntity(collisions.first)->getCollider();
		auto j_collider = getEntity(collisions.second)->getCollider();

		const bool i_IS_STATIC = getEntity(collisions.first)->isStatic();
		const bool j_IS_STATIC = getEntity(collisions.second)->isStatic();

		if (!i_IS_STATIC && j_IS_STATIC) {
			const FloatRect j_BOUNDS = j_collider->getGlobalBounds();
			while (i_collider->isColliding(j_collider)) {
				const FloatRect i_BOUNDS = i_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = i_BOUNDS.intersects(j_BOUNDS);
				if (!intersection.has_value()) {
					break;
				}
				i_collider->resolve(measureDisplacement(i_BOUNDS, j_BOUNDS));
			}
		}
		else if (i_IS_STATIC && !j_IS_STATIC) {
			const FloatRect i_BOUNDS = i_collider->getGlobalBounds();
			while (i_collider->isColliding(j_collider)) {
				const FloatRect j_BOUNDS = j_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = j_BOUNDS.intersects(i_BOUNDS);
				if (!intersection.has_value()) {
					break;
				}
				i_collider->resolve(measureDisplacement(j_BOUNDS, i_BOUNDS));
			}
		}
		else if (!i_IS_STATIC && !j_IS_STATIC) {
			while (i_collider->isColliding(j_collider)) {
				const FloatRect i_BOUNDS = i_collider->getGlobalBounds();
				const FloatRect j_BOUNDS = j_collider->getGlobalBounds();
				std::optional<FloatRect> intersection = i_BOUNDS.intersects(j_BOUNDS);
				if (!intersection.has_value()) {
					break;
				}
				i_collider->resolve(measureDisplacement(i_BOUNDS, j_BOUNDS) * 0.5f);
				j_collider->resolve(measureDisplacement(j_BOUNDS, i_BOUNDS) * 0.5f);
			}
		}
		
		if (p1_collidable != nullptr) {
			p1_collidable->onCollisionExit(collisions.second);
		}
		if (p2_collidable != nullptr) {
			p2_collidable->onCollisionExit(collisions.first);
		}
	}
	m_collisions.clear();
}

void VelocityWithCollisionSystem::detectCollisionsForCollider(std::shared_ptr<Collider>& collider) {
	const unsigned i_LAYER = collider->getLayer();
	const IDtype& i_ID = collider->getOwner()->ID;
	const FloatRect collisionBounds{collider->getGlobalBounds()};

	auto collidingStaticsFound = m_staticColliderTree.search(collisionBounds);
	auto collidingObjectsFound = m_objectsColliderTree.search(collisionBounds);

	for (auto& j_collider : collidingStaticsFound) {
		const unsigned j_LAYER = j_collider->getLayer();
		const IDtype& j_ID = j_collider->getOwner()->ID;
		if (m_collisionLayers.at(i_LAYER).test(j_LAYER)) {
			if(collider->isColliding(j_collider)){
				this->enterCollision(i_ID, j_ID);
			}
		}
	}

	for (auto& k_collider : collidingObjectsFound) {
		const IDtype& k_ID = k_collider->getOwner()->ID;
		if (i_ID == k_ID) {
			continue;
		}
		const unsigned k_LAYER = k_collider->getLayer();
		if (m_collisionLayers.at(i_LAYER).test(k_LAYER)) {
			if (collider->isColliding(k_collider)) {
				this->enterCollision(i_ID, k_ID);
			}
		}

	}

}

void VelocityWithCollisionSystem::enterCollision(IDtype c1, IDtype c2) {
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