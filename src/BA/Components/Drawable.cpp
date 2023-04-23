#include "BA/Components/Drawable.hpp"
#include <BA/Entities/Entity.hpp>

namespace ba {

Drawable::Drawable(ba::Entity* owner, IDtype drawLayer, IDtype sortOrder)
	: Component(owner),
	m_drawLayer(drawLayer),
	m_sortOrder(sortOrder)
{

}

void Drawable::setDrawLayer(IDtype drawLayer) {
	m_drawLayer = drawLayer;
}

IDtype Drawable::getDrawLayer() const {
	return m_drawLayer;
}

void Drawable::setSortOrder(IDtype sortOrder) {
	m_sortOrder = sortOrder;
}

IDtype Drawable::getSortOrder() const {
	return m_sortOrder;
}

} // namespace