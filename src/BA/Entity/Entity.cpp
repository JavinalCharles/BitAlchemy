#include "BA/Entities/Entity.hpp"

unsigned ba::Entity::count = 0u;

namespace ba {

Entity::Entity(ba::SharedContext* context)
	: ID(ba::Entity::count++),
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

std::shared_ptr<ba::Drawable> Entity::getDrawable() const {
	return m_drawable;
}

} // namespace ba