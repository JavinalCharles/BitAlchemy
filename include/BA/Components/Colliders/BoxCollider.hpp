#pragma once

#include <BA/Components/Colliders/Collider.hpp>

namespace ba {

class BoxCollider : public Collider {
public:
	BoxCollider(Entity* owner);

	virtual void awake() override;

	void setSize(const Vector2f& dimension);
	const Vector2f& getSize() const;

	virtual bool isColliding(std::shared_ptr<Collider>& other) override;

	virtual FloatRect getLocalBounds() const override;
	virtual FloatRect getGlobalBounds() const override;
private:
	Vector2f 	m_boxSize{1.f, 1.f};
}; // class BoxCollider

} // namespace ba