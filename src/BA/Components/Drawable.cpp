#include "BA/Components/Drawable.hpp"
#include <BA/Entities/Entity.hpp>

namespace ba {

const IDtype Drawable::CID = ComponentID::DRAWABLE;

Drawable::Drawable(ba::Entity* owner, IDtype drawLayer)
	: Component(owner),
	m_drawLayer(drawLayer)
{

}

void Drawable::setDrawLayer(IDtype drawLayer) {
	m_drawLayer = drawLayer;
}

IDtype Drawable::getDrawLayer() const {
	return m_drawLayer;
}

// void Drawable::setSortOrder(IDtype sortOrder) {
// 	m_sortOrder = sortOrder;
// }

int32 Drawable::getSortOrder() const {
	return static_cast<int32>(m_owner->getPosition().y);
}

} // namespace