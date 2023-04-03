#pragma once

#include <memory>
#include <BA/Components/Boundable.hpp>
#include <BA/Components/Component.hpp>
#include <BA/Utilities/Circle.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

class Collider : public Component, Boundable {
public:
	Collider(Entity* owner);

	void setLayer(unsigned collisionLayer);
	unsigned getLayer() const;

	virtual bool isColliding(std::shared_ptr<Collider>& other) = 0;

	virtual FloatRect getLocalBounds() const = 0;
	virtual FloatRect getGlobalBounds() const = 0;

private:
	unsigned m_layer{};
}; // class Collider

} // namespace ba