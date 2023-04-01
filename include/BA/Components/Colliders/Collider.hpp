#pragma once

#include <BA/Components/Component.hpp>
#include <BA/Utilities/Rect.hpp>

namespace ba {

class Collider : public Component {
public:
	Collider(Entity* owner);

	virtual void awake();

	

	virtual FloatRect getGlobalBounds() const;

private:

}; // class Collider

} // namespace ba