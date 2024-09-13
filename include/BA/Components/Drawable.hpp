#pragma once

#include <memory>
#include "BA/Components/Boundable.hpp"
#include "BA/Components/Component.hpp"
#include "BA/Window/Window.hpp"
#include "BA/Utilities/Rect.hpp"
#include "BA/Types.hpp"

namespace ba {

// TODO: Provide a more modularized/functional means of determining the order of drawables for use by Drawable::getSortOrder()
class Drawable : public Component, Boundable {
public:
	explicit Drawable(Entity* owner, IDtype drawLayer = DEFAULT_RENDER_LAYER);

	virtual void draw(Window& window) = 0;

	void setDrawLayer(IDtype drawLayer);
	IDtype getDrawLayer() const;

	/**
	 * Determines the order of how this drawable will ne sorted
	 * in comparison to other entities within its own DrawLayer.
	 */
	int32 getSortOrder() const;

	virtual FloatRect getLocalBounds() const = 0;
	virtual FloatRect getGlobalBounds() const = 0;

protected:
	// Determines at which layer the drawable will be drawn (i.e. Background, Objects, GUI etc.)
	IDtype m_drawLayer;

public:
	static const IDtype CID; // This number should no longer be in use.

}; // class Drawable

} // namespace ba
