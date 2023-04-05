#include "BA/Entities/Entity.hpp"

unsigned ba::Entity::count = 0u;

namespace ba {

Entity::Entity(ba::SharedContext* context) : 
	Transformable(),
	ID(ba::Entity::count++),
	CONTEXT(context)
{

}

void Entity::awake() {
	for (const auto& component: m_components) {
		component->awake();
	}
}

bool Entity::isStatic() const {
	return m_static;
}

void Entity::setStatic(bool isStatic) {
	m_static = isStatic;
}

bool Entity::isQueuedForRemoval() const {
	return m_queuedForRemoval;
}

void Entity::queueForRemoval(bool remove) {
	m_queuedForRemoval = remove;
}

std::shared_ptr<Drawable> Entity::getDrawable() const {
	return m_drawable;
}

std::shared_ptr<Collider> Entity::getCollider() const {
	return m_collider;
}

} // namespace ba