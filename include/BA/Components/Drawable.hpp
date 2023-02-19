#pragma once

#include <memory>
#include "BA/Components/Component.hpp"
#include "BA/Window/Window.hpp"

namespace ba {

class Drawable : public ba::Component {
public:
	Drawable(ba::Entity* owner, unsigned drawLayer = 0, unsigned sortOrder = 0);

	virtual void draw(ba::Window& window) = 0;

	void setDrawLayer(unsigned drawLayer);
	unsigned getDrawLayer() const;

	void setSortOrder(unsigned sortOrder);
	unsigned getSortOrder() const;

protected:
	// Determines at which layer the drawable will be drawn (i.e. Background, Objects, GUI etc.) 
	unsigned m_drawLayer;

	// Determines how this Drawable will be sorted within its respective layer. Lower sortOrder are drawn first.
	unsigned m_sortOrder;

}; // class Drawable

} // namespace ba