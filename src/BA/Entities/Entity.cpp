#include "BA/Entities/Entity.hpp"

ba::IDtype ba::Entity::count = 0u;

namespace ba {

Entity::Entity(ba::SharedContext* context) :
	Transformable(),
	ID(ba::Entity::count++),
	CONTEXT(context)
{

}

void Entity::awake() {
	for (const auto& [key, component]: m_components) {
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
	if (m_components.contains(ComponentID::DRAWABLE)) {
		return std::dynamic_pointer_cast<Drawable>(m_components.at(ComponentID::DRAWABLE));
	}
	return nullptr;
}

std::shared_ptr<Collider> Entity::getCollider() const {
	if (m_components.contains(ComponentID::COLLIDER)) {
		return std::dynamic_pointer_cast<Collider>(m_components.at(ComponentID::COLLIDER));
	}
	return nullptr;
}

} // namespace ba
