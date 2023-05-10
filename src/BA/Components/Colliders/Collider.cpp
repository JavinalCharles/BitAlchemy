#include <BA/Components/Colliders/Collider.hpp>
#include <BA/Entities/Entity.hpp>

namespace ba {

const IDtype Collider::CID = ComponentID::COLLIDER;

Collider::Collider(Entity* owner) :
	Component(owner)
{

}

void Collider::setLayer(unsigned collisionLayer) {
	m_layer = collisionLayer;
}

unsigned Collider::getLayer() const {
	return m_layer;
}

} // namespace ba