#pragma once

#include <memory>
#include "BA/Components/Boundable.hpp"
#include "BA/Components/Component.hpp"
#include "BA/Window/Window.hpp"
#include "BA/Utilities/Rect.hpp"
#include "BA/Types.hpp"

namespace ba {

class Drawable : public Component, Boundable {
public:
	explicit Drawable(Entity* owner, IDtype drawLayer = 0, IDtype sortOrder = 0);

	virtual void draw(Window& window) = 0;

	void setDrawLayer(IDtype drawLayer);
	IDtype getDrawLayer() const;

	void setSortOrder(IDtype sortOrder);
	IDtype getSortOrder() const;

	virtual FloatRect getLocalBounds() const = 0;
	virtual FloatRect getGlobalBounds() const = 0;

protected:
	// Determines at which layer the drawable will be drawn (i.e. Background, Objects, GUI etc.)
	IDtype m_drawLayer;

	// Determines how this Drawable will be sorted within its respective layer. Lower sortOrder are drawn first.
	IDtype m_sortOrder;
public:
	static const IDtype CID;

}; // class Drawable

} // namespace ba
