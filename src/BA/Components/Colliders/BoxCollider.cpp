#include <BA/Components/Colliders/BoxCollider.hpp>
#include <BA/Entities/Entity.hpp>

namespace ba {

BoxCollider::BoxCollider(Entity* owner) :
	Collider(owner)
{

}

void BoxCollider::awake() {

}

void BoxCollider::setSize(const Vector2f& dimension) {
	m_boxSize = dimension;
}

const Vector2f& BoxCollider::getSize() const {
	return m_boxSize;
}

bool BoxCollider::isColliding(std::shared_ptr<Collider>& other) {
	if(std::dynamic_pointer_cast<BoxCollider>(other)) {
		auto otherBoxCollider = std::dynamic_pointer_cast<BoxCollider>(other);
		return this->getGlobalBounds().intersects(otherBoxCollider->getGlobalBounds()).has_value();
	}

	return false;
}

void BoxCollider::resolve(const Vector2f& resolution) {
	this->getOwner()->move(resolution);
}

FloatRect BoxCollider::getLocalBounds() const {
	return FloatRect{{0.f, 0.f}, m_boxSize};
}

FloatRect BoxCollider::getGlobalBounds() const {
	return getOwner()->getTransform().transformRect(getLocalBounds());
}

} // namespace ba