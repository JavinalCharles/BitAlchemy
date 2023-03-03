#include "BA/Components/Drawable.hpp"
#include <BA/Entities/Entity.hpp>

namespace ba {

Drawable::Drawable(ba::Entity* owner, unsigned drawLayer, unsigned sortOrder)
	: Component(owner),
	m_drawLayer(drawLayer),
	m_sortOrder(sortOrder)
{

}

void Drawable::setDrawLayer(unsigned drawLayer) {
	m_drawLayer = drawLayer;
}

unsigned Drawable::getDrawLayer() const {
	return m_drawLayer;
}

void Drawable::setSortOrder(unsigned sortOrder) {
	m_sortOrder = sortOrder;
}

unsigned Drawable::getSortOrder() const {
	return m_sortOrder;
}

FloatRect Drawable::getGlobalBounds() const {
	return {m_owner->getPosition(), {1.f, 1.f}};
}

} // namespace