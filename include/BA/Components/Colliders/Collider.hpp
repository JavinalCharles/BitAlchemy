#pragma once

#include <memory>
#include <BA/Components/Boundable.hpp>
#include <BA/Components/Component.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

enum class CollidableType : unsigned {
	NONE,
	RECTANGLE_COLLIDER,
	CIRCLE_COLLIDER
};

struct Collidable {
	CollidableType type{};
};


class Collider : public Component, Boundable {
public:
	Collider(Entity* owner);

	void setLayer(unsigned collisionLayer);
	unsigned getLayer() const;

private:
	unsigned m_layer;
}; // class Collider

} // namespace ba